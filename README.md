# Real-Time Embedded Audio Signal Processing System on Raspberry Pi

## Overview

This project is a real-time embedded audio signal processing system built on a Raspberry Pi using C++. The system captures live audio from a USB microphone, processes fixed-size audio blocks, computes signal metrics such as RMS volume, performs FFT-based frequency analysis, and measures processing time to evaluate real-time performance.

The purpose of this project is to demonstrate embedded software design, DSP fundamentals, hardware/software integration, and real-time system thinking in a way that is relevant to aerospace, defense, embedded systems, and DSP software roles.

This is not intended to be only an audio visualization project. The final goal is to build a complete embedded DSP pipeline with acquisition, buffering, frequency-domain analysis, filtering, event detection, and measured timing behavior.

---

## Project Goals

The system is designed to demonstrate:

- Live audio capture from a USB microphone
- Real-time block-based signal processing
- RMS volume measurement
- FFT-based frequency analysis
- Dominant-frequency detection
- Processing-time measurement
- Real-time budget comparison
- Clean C++ and CMake project structure
- Embedded-style architecture with callback, buffer, and processing stages
- Future support for digital filtering, event detection, and hardware outputs

---

## Hardware

Current hardware:

- Raspberry Pi 3 B+
- Raspberry Pi OS
- USB microphone
- MacBook for remote development over SSH

Optional future hardware:

- LEDs
- LCD display
- Buttons
- ESP32 peripheral controller

Current physical layout:

```text
USB Microphone → Raspberry Pi → Wi-Fi/SSH → MacBook
