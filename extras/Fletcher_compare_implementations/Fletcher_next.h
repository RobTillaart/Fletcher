#pragma once
/*
  Author: Daniel Mohr
  Date: 2022-09-10

  Here are implementations, which could be used in the next release.

  Fletcher16.cpp
  Fletcher16.h
  Fletcher32.cpp
  Fletcher32.h
  Fletcher64.cpp
  Fletcher64.h
*/

#define FLETCHER_16_next 255
#define FLETCHER_32_next 65535UL
#define FLETCHER_64_next 4294967295ULL

#if defined(ARDUINO_ARCH_AVR)
uint16_t fletcher16_next(uint8_t *data, const size_t length)
{
  uint8_t _s1 = 0;
  uint8_t _s2 = 0;
  for (size_t i = 0; i < length; i++)
    {
      uint8_t t = 0xFF - data[i];
      if (t >= _s1) _s1 += data[i];
      else _s1 = _s1 + data[i] + 1;

      t = 0xFF - _s1;
      if (t >= _s2) _s2 += _s1;
      else _s2 = _s2 + _s1 + 1;
    }
  return (((uint16_t)_s2) << 8) | _s1;
}
#else
uint16_t fletcher16_next(uint8_t *data, const size_t length)
{
  uint16_t _s1 = 0;
  uint16_t _s2 = 0;
  for (size_t i = 0; i < length; i++)
  {
    _s1 += data[i];
    _s1 = (_s1 & 255) + (_s1 >> 8);
    _s2 += _s1;
    _s2 = (_s2 & 255) + (_s2 >> 8);
  }
  return (((uint16_t)_s2) << 8) | _s1;
}
#endif

uint32_t fletcher32_next(uint16_t *data, const uint16_t length)
{
#ifdef ARDUINO_ARCH_AVR
  uint16_t _s1 = 0;
  uint16_t _s2 = 0;
#else
  uint32_t _s1 = 0;
  uint32_t _s2 = 0;
#endif
  for (uint16_t i = 0; i < length; i++)
    {
#ifdef ARDUINO_ARCH_AVR
      //Serial.println("__builtin_uadd_overflow");
      if (__builtin_uadd_overflow(_s1, data[i], &_s1)) {
	_s1++;
      }
      if (__builtin_uadd_overflow(_s2, _s1, &_s2)) {
	_s2++;
      }
#elif defined(ARDUINO_ARCH_SAMD) || defined(ESP32) || defined(ESP8266)
      _s1 += data[i];
      _s1 = (_s1 & 65535UL) + (_s1 >> 16);
      _s2 += _s1;
      _s2 = (_s2 & 65535UL) + (_s2 >> 16);
#else
      _s1 += data[i];
      if (_s1 >= FLETCHER_32) _s1 -= FLETCHER_32;
      _s2 += _s1;
      if (_s2 >= FLETCHER_32) _s2 -= FLETCHER_32;
#endif
    }
  return (((uint32_t) _s2) << 16) | ((uint32_t) _s1);
}

uint64_t fletcher64_next(uint32_t *data, const uint16_t length)
{
#if defined(ARDUINO_ARCH_SAMD) || defined(ARDUINO_ARCH_AVR)
  uint32_t _s1 = 0;
  uint32_t _s2 = 0;
#else
  uint64_t _s1 = 0;
  uint64_t _s2 = 0;
#endif
  for (uint16_t i = 0; i < length; i++)
    {
#if defined(ARDUINO_ARCH_SAMD) || defined(ARDUINO_ARCH_AVR)
      // bool __builtin_uadd_overflow(unsigned int, unsigned int, unsigned int*)
      // bool __builtin_uaddl_overflow(long unsigned int, long unsigned int, long unsigned int*)
      // bool __builtin_uaddll_overflow(long long unsigned int, long long unsigned int, long long unsigned int*)
      // on SAMD all __builtin_uadd*_overflow work with 32 Bit variables
      // on AVR __builtin_uadd_overflow works with 16 Bit and the others with 32 Bit
      if (__builtin_uaddl_overflow(_s1, data[i], &_s1)) {
	_s1++;
      }
      if (__builtin_uaddl_overflow(_s2, _s1, &_s2)) {
	_s2++;
      }
#elif defined(ESP32) || defined(ESP8266)
      _s1 += data[i];
      _s1 = (_s1 & ((((uint64_t) 1) << 32) - 1)) + (_s1 >> 32);
      _s2 += _s1;
      _s2 = (_s2 & ((((uint64_t) 1) << 32) - 1)) + (_s2 >> 32);
#else
      _s1 += data[i];
      if (_s1 >= FLETCHER_64) _s1 -= FLETCHER_64;
      _s2 += _s1;
      if (_s2 >= FLETCHER_64) _s2 -= FLETCHER_64;
#endif
    }
  return (((uint64_t) _s2) << 32) | ((uint64_t) _s1);
}
