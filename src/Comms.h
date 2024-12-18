//
// Created by Nathan on 10/10/2024.
//
#include <Wire.h>
#ifndef LSM9DS0_COMMS_H
#define LSM9DS0_COMMS_H

// Function to write to specified register
void writeToRegister(uint8_t deviceAddress, uint8_t regAddress, uint8_t value);

#endif //LSM9DS0_COMMS_H
