# Communication Laboratory - Fall 2018
## Course Description
This laboratory-oriented course emphasizes the practical aspects of digital communication, offering hands-on experience with LabView and Matlab, alongside hardware experiments. The coursework incorporates fundamental signal processing techniques, various analog and digital modulation schemes, and application projects.

## Projects Overview
The course encompasses two major projects that provide comprehensive exposure to communication systems and signal processing:

1. **Dual-tone Multi-frequency Signal Detection:** This project involves receiving and detecting Dual-Tone Multi-Frequency (DTMF) signals, a method employed in telephony signaling, using an Arduino Uno. 

2. **Visible Light-based Digital Communication:** This project implements a wireless digital communication system using visible light and Arduino Uno boards. The system utilizes on-off keying signal modulation and ASCII coding for message encoding, supplemented by Manchester coding to mitigate potential timing errors and offsets. 

## Files and Scripts
The repository includes various scripts used in projects and labs, including:

- `simulate_8_PSK.m`: This MATLAB script simulates a digital communication system using 8-PSK (Phase Shift Keying) modulation. The script adds noise to the signal, demodulates it using a nearest-neighbor rule, and finally analyzes and visualizes the error rate of the system.
