#include "n310_modem_cmd_handler_mock.h"

 int cmd_handler_process_iface_data(struct modem_cmd_handler_data *data,
					  struct modem_iface *iface)
{
	struct net_buf *last;
	size_t bytes_read = 0;
	int ret;

	if (!data->rx_buf) {
		data->rx_buf = net_buf_alloc(data->buf_pool,
					     data->alloc_timeout);
		if (!data->rx_buf) {
			/* there is potentially more data waiting */
			return -ENOMEM;
		}
	}

	last = net_buf_frag_last(data->rx_buf);

	/* read all of the data from modem iface */
	while (true) {
		struct net_buf *frag = last;
		size_t frag_room = net_buf_tailroom(frag);

		if (!frag_room) {
			frag = net_buf_alloc(data->buf_pool,
					    data->alloc_timeout);
			if (!frag) {
				/* there is potentially more data waiting */
				return -ENOMEM;
			}

			net_buf_frag_insert(last, frag);
			last = frag;

			frag_room = net_buf_tailroom(frag);
		}

		ret = iface->read(iface, net_buf_tail(frag), frag_room,
				  &bytes_read);
		if (ret < 0 || bytes_read == 0) {
			/* modem context buffer is empty */
			return 0;
		}

		net_buf_add(frag, bytes_read);
	}
}


static bool starts_with(struct net_buf *buf, const char *str)
{
	int pos = 0;

	while (buf && buf->len && *str) {
		if (*(buf->data + pos) == *str) {
			str++;
			pos++;
			if (pos >= buf->len) {
				buf = buf->frags;
				pos = 0;
			}
		} else {
			return false;
		}
	}

	if (*str == 0) {
		return true;
	}

	return false;
}


/* return scanned length for params */
static int parse_params(struct modem_cmd_handler_data *data,  size_t match_len,
			const struct modem_cmd *cmd,
			uint8_t **argv, size_t argv_len, uint16_t *argc)
{
	int i, count = 0;
	size_t begin, end;

	if (!data || !data->match_buf || !match_len || !cmd || !argv || !argc) {
		return -EINVAL;
	}

	begin = cmd->cmd_len;
	end = cmd->cmd_len;
	while (end < match_len) {
		for (i = 0; i < strlen(cmd->delim); i++) {
			if (data->match_buf[end] == cmd->delim[i]) {
				/* mark a parameter beginning */
				argv[*argc] = &data->match_buf[begin];
				/* end parameter with NUL char */
				data->match_buf[end] = '\0';
				/* bump begin */
				begin = end + 1;
				count += 1;
				(*argc)++;
				break;
			}
		}

		if (count >= cmd->arg_count_max) {
			break;
		}

		if (*argc == argv_len) {
			break;
		}

		end++;
	}

	/* consider the ending portion a param if end > begin */
	if (end > begin) {
		/* mark a parameter beginning */
		argv[*argc] = &data->match_buf[begin];
		/* end parameter with NUL char
		 * NOTE: if this is at the end of match_len will probably
		 * be overwriting a NUL that's already ther
		 */
		data->match_buf[end] = '\0';
		(*argc)++;
	}

	/* missing arguments */
	if (*argc < cmd->arg_count_min) {
		return -EAGAIN;
	}

	/*
	 * return the beginning of the next unfinished param so we don't
	 * "skip" any data that could be parsed later.
	 */
	return begin - cmd->cmd_len;
}

/* process a "matched" command */
static int process_cmd(const struct modem_cmd *cmd, size_t match_len,
			struct modem_cmd_handler_data *data)
{
	int parsed_len = 0, ret = 0;
	uint8_t *argv[20];
	uint16_t argc = 0U;

	/* reset params */
	memset(argv, 0, sizeof(argv[0]) * ARRAY_SIZE(argv));

	/* do we need to parse arguments? */
	if (cmd->arg_count_max > 0U) {
		/* returns < 0 on error and > 0 for parsed len */
		parsed_len = parse_params(data, match_len, cmd,
					  argv, ARRAY_SIZE(argv), &argc);
		if (parsed_len < 0) {
			return parsed_len;
		}
	}

	/* skip cmd_len + parsed len */
	data->rx_buf = net_buf_skip(data->rx_buf, cmd->cmd_len + parsed_len);

	/* call handler */
	if (cmd->func) {
		ret = cmd->func(data, match_len - cmd->cmd_len - parsed_len,
				argv, argc);
		if (ret == -EAGAIN) {
			/* wait for more data */
			net_buf_push(data->rx_buf, cmd->cmd_len + parsed_len);
		}
	}

	return ret;
}



 bool is_crlf(uint8_t c)
{
	if (c == '\n' || c == '\r') {
		return true;
	} else {
		return false;
	}
}


static uint16_t findcrlf(struct modem_cmd_handler_data *data,
		      struct net_buf **frag, uint16_t *offset)
{
	struct net_buf *buf = data->rx_buf;
	uint16_t len = 0U, pos = 0U;

	while (buf && buf->len && !is_crlf(*(buf->data + pos))) {
		if (pos + 1 >= buf->len) {
			len += buf->len;
			buf = buf->frags;
			pos = 0U;
		} else {
			pos++;
		}
	}

	if (buf && buf->len && is_crlf(*(buf->data + pos))) {
		len += pos;
		*offset = pos;
		*frag = buf;
		return len;
	}

	return 0;
}


 void skipcrlf(struct modem_cmd_handler_data *data)
{
	while (data->rx_buf && data->rx_buf->len &&
			is_crlf(*data->rx_buf->data)) {
		net_buf_pull_u8(data->rx_buf);
		if (!data->rx_buf->len) {
			data->rx_buf = net_buf_frag_del(NULL, data->rx_buf);
		}
	}
}

 void cmd_handler_process_rx_buf(struct modem_cmd_handler_data *data)
{
	const struct modem_cmd *cmd;
	struct net_buf *frag = NULL;
	size_t match_len;
	int ret;
	uint16_t offset, len;

	/* process all of the data in the net_buf */
	while (data->rx_buf && data->rx_buf->len) {
		skipcrlf(data);
		if (!data->rx_buf || !data->rx_buf->len) {
			break;
		}

		cmd = find_cmd_direct_match(data);
		if (cmd && cmd->func) {
			ret = cmd->func(data, cmd->cmd_len, NULL, 0);
			if (ret == -EAGAIN) {
				/* Wait for more data */
				break;
			} else if (ret > 0) {
				//LOG_DBG("match direct cmd [%s] (ret:%d)",
				//	log_strdup(cmd->cmd), ret);
				data->rx_buf = net_buf_skip(data->rx_buf, ret);
			}

			continue;
		}

		frag = NULL;
		/* locate next CR/LF */
		len = findcrlf(data, &frag, &offset);
		if (!frag) {
			/*
			 * No CR/LF found.  Let's exit and leave any data
			 * for next time
			 */
			break;
		}

		/* load match_buf with content up to the next CR/LF */
		/* NOTE: keep room in match_buf for ending NUL char */
		match_len = net_buf_linearize(data->match_buf,
					      data->match_buf_len - 1,
					      data->rx_buf, 0, len);
		if ((data->match_buf_len - 1) < match_len) {
		//	LOG_ERR("Match buffer size (%zu) is too small for "
		//		"incoming command size: %u!  Truncating!",
		//		data->match_buf_len - 1, match_len);
		}

#if defined(CONFIG_MODEM_CONTEXT_VERBOSE_DEBUG)
		LOG_HEXDUMP_DBG(data->match_buf, match_len, "RECV");
#endif

		k_sem_take(&data->sem_parse_lock, K_FOREVER);

		cmd = find_cmd_match(data);
		if (cmd) {
			//LOG_DBG("match cmd [%s] (len:%u)",
		//		log_strdup(cmd->cmd), match_len);

			if (process_cmd(cmd, match_len, data) == -EAGAIN) {
				k_sem_give(&data->sem_parse_lock);
				break;
			}

			/*
			 * make sure we didn't run out of data during
			 * command processing
			 */
			if (!data->rx_buf) {
				/* we're out of data, exit early */
				k_sem_give(&data->sem_parse_lock);
				break;
			}

			frag = NULL;
			/*
			 * We've handled the current line.
			 * Let's skip any "extra" data in that
			 * line, and look for the next CR/LF.
			 * This leaves us ready for the next
			 * handler search.
			 * Ignore the length returned.
			 */
			(void)findcrlf(data, &frag, &offset);
		}

		k_sem_give(&data->sem_parse_lock);

		if (frag && data->rx_buf) {
			/* clear out processed line (net_buf's) */
			while (frag && data->rx_buf != frag) {
				data->rx_buf = net_buf_frag_del(NULL,
								data->rx_buf);
			}

			net_buf_pull(data->rx_buf, offset);
		}
	}
}


/*
 * check 3 arrays of commands for a match in match_buf:
 * - response handlers[0]
 * - unsolicited handlers[1]
 * - current assigned handlers[2]
 */
 const struct modem_cmd *find_cmd_match(
		struct modem_cmd_handler_data *data)
{
	int j, i;

	for (j = 0; j < ARRAY_SIZE(data->cmds); j++) {
		if (!data->cmds[j] || data->cmds_len[j] == 0U) {
			continue;
		}

		for (i = 0; i < data->cmds_len[j]; i++) {
			/* match on "empty" cmd */
			if (strlen(data->cmds[j][i].cmd) == 0 ||
			    strncmp(data->match_buf, data->cmds[j][i].cmd,
				    data->cmds[j][i].cmd_len) == 0) {
				return &data->cmds[j][i];
			}
		}
	}

	return NULL;
}

 const struct modem_cmd *find_cmd_direct_match(
		struct modem_cmd_handler_data *data)
{
	int j, i;

	for (j = 0; j < ARRAY_SIZE(data->cmds); j++) {
		if (!data->cmds[j] || data->cmds_len[j] == 0U) {
			continue;
		}

		for (i = 0; i < data->cmds_len[j]; i++) {
			/* match start of cmd */
			if (data->cmds[j][i].direct &&
			    (data->cmds[j][i].cmd[0] == '\0' ||
			     starts_with(data->rx_buf, data->cmds[j][i].cmd))) {
				return &data->cmds[j][i];
			}
		}
	}

	return NULL;
}