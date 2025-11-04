This is a repository for my mostly Arduino and STM32 tinkering projects.

**7 segment diplay**

A simple potentiometer controlled 7 segment display which is driven by a 7 segment decoder.

![](/assets/7-segment-display.png?raw=true)

**Bit-Bagning**

This project involves bare metal MCU programming. Using bit manipulation a PWM signal is being generated pin non PWM enabled pins on Arduino.

![[bit-banging.png]]

**Bit Banging  2**

This project lights up two LEDs for different time intervals: YELLOW 1 second on / 1 second off, and GREEN 1 minute on / 1 minute off.
The whole process is once again managed by bit and register manipulation

![[bit-banging2.png]]

**UART communication**

Arduino 1: Has 2 buttons connected, reads data from them, sends 1 character of data via UART, depending on which button is pressed.

Arduino 2: Reads the data from the UART, depending on the received character, turns on either the red or green LED.

When the first button is pressed, the red LED should turn on, the green LED should turn off, and stay that way.

When the second button is pressed, the green LED turns on, while the red LED turns off.

![[uart.png]]
