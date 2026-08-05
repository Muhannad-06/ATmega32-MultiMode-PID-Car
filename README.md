# Multi-Mode Autonomous & Teleoperated Vehicle (ATmega32)

## Overview
An embedded systems diploma project centered around a versatile 3-in-1 robotic car driven by the Microchip ATmega32 8-bit AVR microcontroller. The system integrates closed-loop PID feedback control for high-precision line tracking, ultrasonic distance measurement for collision avoidance, and a wireless UART control interface.

## Key Operational Modes
* **PID Line Follower Mode:** Uses a 5-channel IR sensor array to compute positional error and applies a Proportional-Integral-Derivative (PID) algorithm for smooth line tracking and sharp turn negotiation.
* **Obstacle Avoidance Mode:** Employs an HC-SR04 ultrasonic sensor with Timer1 high-resolution pulse-width measurement for real-time proximity detection and autonomous rerouting.
* **Manual Control Mode:** Uses an HC-05/06 Bluetooth module over hardware USART to process remote driving commands from a smartphone app.

## Hardware & Peripheral Architecture
* **Core MCU:** ATmega32 running on 8/16 MHz external oscillator.
* **Motor Drive:** Timer0 (`OC0`) & Timer2 (`OC2`) 8-bit Fast PWM driving an L298N / L293D dual H-Bridge.
* **Sensors:** 5-Channel IR sensor bar (Port A ADC/GPIO) and HC-SR04 Ultrasonic module.
* **Communication:** Hardware USART (9600 Baud) for low-latency command parsing.
* **Firmware Design:** Non-blocking Finite State Machine (FSM) written in bare-metal C.
