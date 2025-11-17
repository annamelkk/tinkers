This is a repository for my mostly Arduino and STM32 tinkering projects.

**7 segment diplay**

A simple potentiometer controlled 7 segment display which is driven by a 7 segment decoder.

![](/assets/7-segment-display.png?raw=true)

**Bit-Bagning**

This project involves bare metal MCU programming. Using bit manipulation a PWM signal is being generated pin non PWM enabled pins on Arduino.

![](/assets/bit-banging.png?raw=true)

**Bit Banging  2**

This project lights up two LEDs for different time intervals: YELLOW 1 second on / 1 second off, and GREEN 1 minute on / 1 minute off.
The whole process is once again managed by bit and register manipulation

![](/assets/bit-banging2.png?raw=true)


**UART communication**

Arduino 1: Has 2 buttons connected, reads data from them, sends 1 character of data via UART, depending on which button is pressed.

Arduino 2: Reads the data from the UART, depending on the received character, turns on either the red or green LED.

When the first button is pressed, the red LED should turn on, the green LED should turn off, and stay that way.

When the second button is pressed, the green LED turns on, while the red LED turns off.

![](/assets/uart.png?raw=true)

**Minute Timer**

The goal of this task is to make a timer that shows the time from startup in MM:SS format.

I need to use four separate 7-segment displays connected to a **single** Arduino UNO R3 board. 

One solution is with BCD to 7 segment decoders. For each display a we take a CD4511 chip and then using software assign each display the respective digit.

Thanks to these chips we decrease the amount of GPIO pins needed from $7 \cdot 4 = \underline{28}$ to $4 \cdot 4 = \underline{16}$. 

However we have only 14 digital input/output pins. Thankfully the analog pins on ATmega328P, which is the chip on which Arduino Uno R3 based does not have ADC-only pins, so we can use ADC pins as GPIOs.

![](/assets/minute-timer.png?raw=true)