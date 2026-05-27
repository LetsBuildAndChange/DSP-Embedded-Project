# Real-Time Embedded Audio Signal Processing System on Raspberry Pi

## Project Overview

This project is a real-time embedded audio signal processing system built on a Raspberry Pi using C++.

The goal is to capture live audio from a USB microphone, process the signal in real time, measure timing behavior, and eventually add DSP features such as FFT-based frequency detection, filtering, event detection, and embedded hardware outputs.

This project is intended to demonstrate embedded software design, DSP fundamentals, real-time thinking, Linux audio programming, and clean C++ system architecture.

---

## System Goal

Build a real-time audio pipeline that can:

- Capture live audio from a USB microphone
- Process audio in fixed-size blocks
- Compute time-domain signal metrics such as RMS
- Perform FFT-based frequency analysis
- Detect dominant frequencies
- Measure processing time against a real-time budget
- Eventually support filtering, event detection, and hardware outputs

The project is not just an audio graphing demo. The goal is to build and explain a real-time embedded DSP pipeline.

---

## Hardware

Current hardware:

- Raspberry Pi 3 B+
- Raspberry Pi OS
- USB microphone
- MacBook used for SSH / remote development
- Official Raspberry Pi power supply
- microSD card

Optional future peripherals:

- LEDs
- LCD display
- Buttons
- ESP32 peripheral controller

Current physical setup:

```text
USB Microphone → Raspberry Pi → Wi-Fi/SSH → MacBook
