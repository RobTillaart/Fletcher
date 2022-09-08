//
//    FILE: Fletcher64.cpp
//  AUTHOR: Rob Tillaart
// PURPOSE: Arduino class for Fletcher32
//     URL: https://github.com/RobTillaart/Fletcher


#include "Fletcher64.h"

#define FLETCHER_64                       4294967295ULL



Fletcher64::Fletcher64()
{
  begin();
}


void Fletcher64::begin(uint32_t s1, uint32_t s2)
{
  _s1    = s1;
  _s2    = s2;
  _count = 0;
}


void Fletcher64::add(uint32_t value)
{
  _count++;
#if defined(ARDUINO_ARCH_SAMD) || defined(ARDUINO_ARCH_AVR)
  // bool __builtin_uadd_overflow(unsigned int, unsigned int, unsigned int*)
  // bool __builtin_uaddl_overflow(long unsigned int, long unsigned int, long unsigned int*)
  // bool __builtin_uaddll_overflow(long long unsigned int, long long unsigned int, long long unsigned int*)
  // on SAMD all __builtin_uadd*_overflow work with 32 Bit variables
  // on AVR __builtin_uadd_overflow works with 16 Bit and the others with 32 Bit
  if (__builtin_uaddl_overflow(_s1, value, &_s1)) {
    _s1++;
  }
  if (__builtin_uaddl_overflow(_s2, _s1, &_s2)) {
    _s2++;
  }
#elif defined(ESP32) || defined(ESP8266)
  _s1 += value;
  _s1 = (_s1 & ((((uint64_t) 1) << 32) - 1)) + (_s1 >> 32);
  _s2 += _s1;
  _s2 = (_s2 & ((((uint64_t) 1) << 32) - 1)) + (_s2 >> 32);
#else
  _s1 += value;
  if (_s1 >= FLETCHER_64) _s1 -= FLETCHER_64;
  _s2 += _s1;
  if (_s2 >= FLETCHER_64) _s2 -= FLETCHER_64;
#endif
}


void Fletcher64::add(const uint32_t * array, uint16_t length)
{
  while (length--)
  {
    add(*array++);
  }
}


// -- END OF FILE --

