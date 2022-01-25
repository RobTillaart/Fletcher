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
  // assertEqual( 32, GAMMA_DEFAULT_SIZE);
  // assertEqual(256, GAMMA_MAX_SIZE);
}


unittest(test_constructor)
{
  /*
  GAMMA gt0;  // uses default 32 size
  gt0.begin();
  assertEqual(33, gt0.size());
  assertEqualFloat(2.8, gt0.getGamma(), 0.0001);
  assertEqual(28,  gt0.distinct());
*/
}


unittest_main()

// --------
