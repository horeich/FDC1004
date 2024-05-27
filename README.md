# Texas Instrument FDC1004 (in progress)

Driver library for Texas Instrument FDC1004 using mbedOS. The device uses an I2C communication interface

## Overview
### Required hardware
For quick prototyping the following hardware is recommended:
- [NUCLEO-L476RG](https://os.mbed.com/platforms/ST-Nucleo-L476RG/) - a simple STM32 development board
- [Texas Instruments-FDC1004](https://www.digikey.com/en/products/detail/texas-instruments/FDC1004DSCR/6571851) - a high precision temperature sensor breakout board

The library works with any board supported by mbedOS

### Library features
- [x] Full support of every device functionality
- [x] Easy to use API - write easily readable code within minutes

## Software design
The registers of the fdc1004 device are 16-bit wide

### Constraints
It is worth noting the following constraints:
- Channel A must always be smaller than Channel B (in case of differential measurement)
- CAPDAC is only available on Channel B and its value cannot exceed 31
- Gain can be calibrated in the range of 0.00 to 3.99
- Offset can be calibrated in the range of -16pF to 16pF

## Tests
### Unit tests
TODO
### Integration tests
Basic integration test for each function; does not include larger tests with temperature read-outs yet

### Run Examples
- 
### level_sensor.cpp
This example shows how to use this sensor as a level measurement sensor
- enable the relevant channels
- call the measure(Channel) function for the enabled channels to get the measurement