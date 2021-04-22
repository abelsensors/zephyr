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

You will see this error if you try to build Blinky for an unsupported board:

.. code-block:: none

   Unsupported board: led0 devicetree alias is not defined

The board must have an LED connected via a GPIO pin. These are called "User
LEDs" on many of Zephyr's :ref:`boards`. The LED must be configured using the
``led0`` :ref:`devicetree <dt-guide>` alias. This is usually done in the
:ref:`BOARD.dts file <devicetree-in-out-files>` or a :ref:`devicetree overlay
<set-devicetree-overlays>`.

Building and Running
********************

Build and flash Blinky as follows, changing ``reel_board`` for your board:

.. zephyr-app-commands::
   :zephyr-app: samples/basic/blinky
   :board: reel_board
   :goals: build flash
   :compact:

After flashing, the LED starts to blink. Blinky does not print to the console.
