# Pico Clock Frequency Switcher

A simple Raspberry Pi Pico project that generates a clock signal with two selectable frequencies.

## Overview

This program configures a Raspberry Pi Pico to output a clock signal on one GPIO pin while allowing the frequency to be switched between two preset values using a toggle input on another GPIO pin.

- Primary clock frequency: 26.873 MHz
- Secondary clock frequency: 28.656 MHz
- Frequency selection via GPIO pin

## Pin Configuration

- **GPIO 0**: Clock selection input pin
    - LOW (0V) = 26.873 MHz
    - HIGH (3.3V) = 28.656 MHz
- **GPIO 1**: Clock output pin

## Wiring Diagram

```
Raspberry Pi Pico
+-----------------+
|                 |
| GPIO 0 --------+--- Switch to GND/3.3V for frequency selection
|                 |
| GPIO 1 --------+--- Clock output signal
|                 |
| GND ------------+--- Ground
|                 |
+-----------------+
```

## How It Works

The program:

1. Initializes GPIO 0 as an input pin for clock selection
2. Configures GPIO 1 as a PWM output pin initially set to the first frequency
3. Continuously monitors the state of the clock selection pin
4. Switches the clock frequency when the selection pin state changes
5. Uses the Pico's PWM hardware to generate a stable clock signal

The code uses the PWM hardware to generate a square wave with a duty cycle close to 50%. It's marked with `__time_critical_func()` to ensure timing precision.

## Building and Flashing

### Prerequisites

- Raspberry Pi Pico C/C++ SDK
- CMake
- Build tools (make, gcc, etc.)

### Build Instructions

1. Set up the Pico SDK environment:

```bash
export PICO_SDK_PATH=/path/to/pico-sdk
```

2. Create a build directory and run CMake:

```bash
mkdir build
cd build
cmake ..
make
```

3. Connect the Pico in BOOTSEL mode and copy the generated .uf2 file to it:

```bash
cp pico-oscillator.uf2 /path/to/pico
```

## Applications

This project can be useful for:
- Testing clock-dependent peripherals
- Clock-sensitive timing experiments
- Generating reference clock signals for other devices

## License

MIT License

## Contributing

Contributions, issues, and feature requests are welcome!