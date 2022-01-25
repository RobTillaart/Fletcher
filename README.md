
[![Arduino CI](https://github.com/RobTillaart/FLETCHER/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/FLETCHER/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/FLETCHER/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/FLETCHER/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/FLETCHER/actions/workflows/jsoncheck.yml)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/FLETCHER/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/FLETCHER.svg?maxAge=3600)](https://github.com/RobTillaart/FLETCHER/releases)


# FLETCHER

Arduino Library for Fletchers checksum


## Description

This library is provides a Fletcher checksum.

It is in general faster than CRC but not as good in detecting errors.
See https://en.wikipedia.org/wiki/Fletcher%27s_checksum for details.


## Interface

- **fletcher16(uint8_t \*data, uint16_t length)**
- **fletcher32(uint16_t \*data, uint16_t length)**
- **fletcher64(uint32_t \*data, uint16_t length)**


## Operation

See example


## Future ideas

- improve documentation
- test other platforms
- Class versions
  - incremental calculate e.g. for a stream.
- look for optimizations 
- 

