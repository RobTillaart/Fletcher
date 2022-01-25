//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2022-01-25
// PURPOSE: unit tests for the GAMMA library
//          https://github.com/RobTillaart/GAMMA
//          https://github.com/Arduino-CI/arduino_ci/blob/master/REFERENCE.md
//

// supported assertions
// https://github.com/Arduino-CI/arduino_ci/blob/master/cpp/unittest/Assertion.h#L33-L42
// ----------------------------
// assertEqual(expected, actual)
// assertNotEqual(expected, actual)
// assertLess(expected, actual)
// assertMore(expected, actual)
// assertLessOrEqual(expected, actual)
// assertMoreOrEqual(expected, actual)
// assertTrue(actual)
// assertFalse(actual)
// assertNull(actual)
// assertNotNull(actual)

#include <ArduinoUnitTests.h>


#include "Arduino.h"
#include "Fletcher.h"



unittest_setup()
{
  fprintf(stderr, "FLETCHER_LIB_VERSION: %s\n", (char *) FLETCHER_LIB_VERSION);
}

unittest_teardown()
{
}


unittest(test_constants)
{
  assertEqual(FLETCHER_16, 255);
  assertEqual(FLETCHER_16, 65535UL);
  assertEqual(FLETCHER_16, 4294967295ULL);
}


unittest(test_fletcher16)
{
  char str1[24] = "abcde";
  char str2[24] = "abcdef";
  char str3[24] = "abcdefgh";
  
  assertEqual(51440, fletcher16((uint8_t *) str1, 5));
  assertEqual( 8279, fletcher16((uint8_t *) str2, 6));
  assertEqual( 1575, fletcher16((uint8_t *) str3, 8));
}


unittest(test_fletcher32)
{
  char str1[24] = "abcde";
  char str2[24] = "abcdef";
  char str3[24] = "abcdefgh";
  
  assertEqual(4031760169, fletcher32((uint16_t *) str1, 3));
  assertEqual(1448095018, fletcher32((uint16_t *) str2, 3));
  assertEqual(3957429649, fletcher32((uint16_t *) str3, 4));
}


unittest(test_fletcher64)
{
  char str1[24] = "abcde";
  char str2[24] = "abcdef";
  char str3[24] = "abcdefgh";
  
  assertEqual(14467467625952928454, fletcher64((uint32_t *) str1, 2));
  assertEqual(14467579776138987718, fletcher64((uint32_t *) str2, 2));
  assertEqual( 3543817411021686982, fletcher64((uint32_t *) str3, 2));
}


unittest_main()

// --------
