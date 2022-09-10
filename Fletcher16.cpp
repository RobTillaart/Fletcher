//
//    FILE: Fletcher16.cpp
//  AUTHOR: Rob Tillaart, Daniel Mohr
// PURPOSE: Arduino class for Fletcher16
//     URL: https://github.com/RobTillaart/Fletcher


#include "Fletcher16.h"

#define FLETCHER_16                       255


Fletcher16::Fletcher16()
{
  begin();
}


void Fletcher16::begin(uint8_t s1, uint8_t s2)
{
  _s1    = s1;
  _s2    = s2;
  _count = 0;
}


void Fletcher16::add(uint8_t value)
{
  _count++;
#if defined(ARDUINO_ARCH_AVR)
  uint8_t t = 0xFF - value;
  if (t >= _s1) _s1 += value;
  else _s1 = _s1 + value + 1;
  
  t = 0xFF - _s1;
  if (t >= _s2) _s2 += _s1;
  else _s2 = _s2 + _s1 + 1;

#else
  _s1 += value;
  _s1 = (_s1 & 255) + (_s1 >> 8);
  _s2 += _s1;
  _s2 = (_s2 & 255) + (_s2 >> 8);
#endif
}

void Fletcher16::add(const uint8_t * array, uint16_t length)
{
  while (length--)
  {
    add(*array++);
  }
}

uint16_t Fletcher16::getFletcher() {
  _s1 = _s1 % 255;
  _s2 = _s2 % 255;
  return (((uint16_t)_s2) << 8) | _s1;
};

// -- END OF FILE --

