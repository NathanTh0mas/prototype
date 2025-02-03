//
// Created by Nathan on 18/12/2024.
//
#ifndef IMU_H
#define IMU_H

#include <Arduino.h>
#include "Adafruit_LSM9DS0.h"
#include "MadgwickAHRS.h"

// IMU-related constants (localized here instead of global)
constexpr float X_SCALE_FACTOR = 2.0f;
constexpr float G_SCALE_FACTOR = 245.0f;
constexpr float M_SCALE_FACTOR = 4.0f;

// Thresholds
constexpr float FREE_FALL_THRESHOLD = 0.5f;
constexpr float IMPACT_THRESHOLD = 2.5f;
constexpr unsigned long FALL_DURATION = 200;
constexpr float ROLL_THRESHOLD = 45.0f;
constexpr float PITCH_THRESHOLD = 45.0f;

// Function prototypes
void setupIMU();
void updateIMUData();

// Optional: If needed elsewhere, provide getters
float getRoll();
float getPitch();


#endif // IMU_H