# Morse Code Translator

## Overview

The Morse Code Translator is a project that uses a Raspberry Pi to flash a message in Morse code to an LED. This Morse code message is then detected by a photodiode connected to a GPIO pin on the ESP32C3 board. The code reads the voltage received through the photodiode and translates the Morse code message into English.

## How it Works

1. The Raspberry Pi flashes a message in Morse code using an LED.
2. A photodiode connected to a GPIO pin on the ESP32C3 board detects the flashes of light.
3. The ESP32C3 board reads the voltage variations from the photodiode.
4. The code running on the ESP32C3 interprets the Morse code pattern and translates it into English characters.
5. The translated message is made available for further processing or display.

## Usage

To use this Morse Code Translator project, you will need the following components:

- Raspberry Pi
- ESP32C3 board
- LED
- Photodiode
- Wiring and power supply as needed
