# Rotary Encoder Based Embedded System Experiment

## Project Overview
This project demonstrates a simple embedded system using a **rotary encoder** as an input device and an **LED** as an output device.  
The user rotates the encoder to increase or decrease a counter value. According to that value, the system controls the LED directly.

This experiment is useful for understanding basic embedded systems concepts such as:
- digital input reading
- user interaction
- counter logic
- output control

---

## What is a Rotary Encoder?
A rotary encoder is a digital input device used in embedded systems to detect rotational movement.

It can tell the microcontroller:
- whether the knob is turning
- which direction it is turning
- whether the button is pressed

Unlike a potentiometer, a rotary encoder does not provide a direct analog value.  
Instead, it produces digital pulses that the Arduino reads step by step.

Rotary encoders are commonly used in:
- menu navigation systems
- volume control
- machine settings
- speed adjustment panels
- embedded control interfaces

---

## Rotary Encoder Pins
The rotary encoder module used in this project has the following pins:

- **GND** → Ground
- **+** → 5V power supply
- **SW** → Push button signal
- **DT** → Data signal
- **CLK** → Clock signal

### Pin Functions
- **GND**: connected to Arduino GND
- **+**: connected to Arduino 5V
- **SW**: used to detect button press
- **DT** and **CLK**: used together to detect rotation direction

---

## Aim of the Experiment
The aim of this experiment is to show how a rotary encoder can be used as a **human-machine interface** in an embedded system.

The user changes the system level by rotating the encoder, and the system responds by controlling an LED directly according to the counter value.

---

## Components Used
- Arduino Uno
- Rotary Encoder Module
- 1 LED
- 1 resistor (220 ohm)
- jumper wires
- breadboard or Wokwi simulation environment

---

## Pin Connections

### Rotary Encoder
- **GND** → Arduino **GND**
- **+** → Arduino **5V**
- **CLK** → Arduino **D2**
- **DT** → Arduino **D3**
- **SW** → Arduino **D4**

### LED
- LED anode → Arduino **D8**
- LED cathode → **220 ohm resistor** → **GND**

---

## How the System Works
1. The rotary encoder is turned by the user.
2. The Arduino reads the encoder pulses.
3. The counter value increases or decreases.
4. If the counter reaches a selected threshold, the LED turns on.
5. If the button on the encoder is pressed, the counter resets.

In this simple version:
- if `counter < 5`, the LED stays OFF
- if `counter >= 5`, the LED turns ON

---

 
