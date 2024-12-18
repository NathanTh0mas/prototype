//
// Created by Nathan on 10/10/2024.
//
#include <Wire.h>
#include "Comms.h"

// Function to write to specified register
void writeToRegister(uint8_t deviceAddress, uint8_t regAddress, uint8_t value) {
    Wire.beginTransmission(deviceAddress);
    Wire.write(regAddress);
    Wire.write(value);
    Wire.endTransmission();
}

