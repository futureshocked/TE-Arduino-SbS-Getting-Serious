/*
 * Copyright 2017, Helium Systems, Inc.
 * All Rights Reserved. See LICENCE.txt for license information
 */

#ifndef BOARD_H
#define BOARD_H


#if defined(ARDUINO_AVR_UNO)
#include "SoftwareSerial.h"
SoftwareSerial atom_serial(7, 8);
#define HELIUM_BAUD_RATE helium_baud_b9600

#elif defined(ARDUINO_SAM_ZERO)
// Arduino M0 Pro
#define atom_serial Serial5

#elif defined(ARDUINO_SAMD_ZERO)
// Arduino Zero
#define atom_serial Serial1

#elif defined(ARDUINO_SAM_DUE)
// Arduino Due with Serial3 (pin 15, 14)
// mapped to pin 8, 9 on the adapter
#define atom_serial Serial3


#endif

#ifndef HELIUM_BAUD_RATE
#define HELIUM_BAUD_RATE helium_baud_b115200
#endif


#endif // BOARD_H
