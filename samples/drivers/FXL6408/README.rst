.. _FXL6408-sample:

FXL6408 gpio-expander
#####################

Overview
********

This is a simple application to show usage of the FXL6408 gpio-expander. The
sample showcases configuring pins as input/output and as pull-up or pull-down.
Furthermore it shows how to read or write to the pins. The FXL6408 driver is
useing the :ref:`GPIO API <gpio_api>`.

.. _FXL6408-sample-requirements:

Requirements
************

For the sample to work, the FXL6408 I2C adres must be configured as 0x43.
Furtermore, to showcase writing to the expanders pins, there must be LEDs
connected to pins 4-7.

Building and Running
********************

Build and flash the FXL6408-sample as follows, changing ``reel_board`` for
your board:

.. zephyr-app-commands::
   :zephyr-app: samples/basic/blinky
   :board: reel_board
   :goals: build flash
   :compact:

After flashing, the LEDs connected to the FXL6408 will start to blink and it
will use the console to print the values read from pins.

Sample output
=============

In this example pin 0 and 1 are briefly connected to ground followed by pin 2
and 3 being connected to Vcc. The default value is 3 since in this sample
pin 0 and 1 are configured as pull-up.

.. code-block:: console

   result: 3
   result: 3
   result: 3
   result: 1
   result: 2
   result: 7
   result: 11
