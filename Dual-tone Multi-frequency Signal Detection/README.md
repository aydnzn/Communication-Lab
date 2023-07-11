# Dual-Tone Multi-Frequency Signal Detection
The aim of the project is to receive and detect Dual-Tone Multi-Frequency (DTMF) signals used in classic telephone signalling with Arduino Uno.

## Project Overview
The DTMF system uses a set of eight audio frequencies transmitted in pairs to represent 16 signals. This project will involve separating these DTMF signals with digital low/high/band pass filtering and then detecting individual tones.

For more information about DTMF signals, refer to [Wikipedia](https://en.wikipedia.org/wiki/Dual-tone_multi-frequency_signaling).

## Obtaining the DTMF Signals
DTMF signals can be generated using a standard audio jack connected to a PC or smartphone. The signal is then fed into the Arduino via the "Analog Input". The Arduino samples and quantizes this analog signal, converting it into the digital domain.

- PC DTMF generator: [Online Tone Generator](http://onlinetonegenerator.com/dtmf.html)
- Android App: [Tone Generator](https://play.google.com/store/apps/details?id=com.amknott.ToneGen)

## System Requirements
The designed system should detect the DTMF signals within an acceptable time frame. The detected DTMF signals will need to be displayed on the screen (such as in the form of 053xxxxxxxx). Arduino can either be used simply as an analog-to-digital converter or the processing can be done on the Arduino board.

## Useful Links
- [Arduino - AnalogRead](https://www.arduino.cc/en/Reference/AnalogRead)
- [Arduino - Serial.Write](https://www.arduino.cc/en/Serial/Write)
- [MATLAB - fopen](http://www.mathworks.com/help/matlab/ref/serial.fopen.html)
- [MATLAB - Baudrate](http://www.mathworks.com/help/matlab/matlab_external/baudrate.html)

## Equipment & Components
The project uses Arduino Uno and possibly other components including resistors, capacitors, transistors, integrated circuits, stereo jack/cables, jumper cables.

## Contents

### aydinuzun_1.ino

This Arduino script reads a value from the analog pin 0, scales it down to a byte value, and then writes this value to the serial port. This might be used to read data from a sensor, and then send this data to a computer over the serial port.

### Aydın_Uzun_EE_479_Project_I.pdf

This is the project report for Project 1. It contains detailed information about the project implementation, design choices, and results.

### Aydın_Uzun_EE_479_Project_I.m

This is the MATLAB script related to the project. It includes the detailed implementation of the project algorithm.

### Project1_description.pdf

This is the original project description file. It provides the requirements and instructions for the project.