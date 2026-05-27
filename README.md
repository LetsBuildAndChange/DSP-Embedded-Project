# Real-Time Embedded Audio Signal Processing System on Raspberry Pi

## Overview

This project is a real-time embedded audio signal processing system built on a Raspberry Pi using C++. The system captures live audio from a USB microphone, processes fixed-size audio blocks, computes signal metrics such as RMS volume, performs FFT-based frequency analysis, and measures processing time to evaluate real-time performance.

The goal is to demonstrate embedded software design, DSP fundamentals, hardware/software integration, and real-time system thinking.

## Project Goals

The system is designed to show:

- Live audio capture from a USB microphone
- Real-time block-based signal processing
- RMS volume measurement
- FFT-based frequency analysis
- Dominant-frequency detection
- Processing-time measurement
- Real-time budget comparison
- Clean C++/CMake project structure
- Future support for filtering, event detection, and hardware outputs

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

## System Architecture

Current architecture:

```text
USB Microphone
   ↓
Raspberry Pi
   ↓
PortAudio input callback
   ↓
Audio block processing
   ↓
RMS / FFT / timing metrics
   ↓
Terminal output
