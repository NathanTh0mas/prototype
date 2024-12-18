//
// Created by Nathan on 18/12/2024.
//

#ifndef GLOBALS_H
#define GLOBALS_H

#include <Arduino.h>            // Explicitly include Arduino core functions
#include <Wire.h>               // For I2C communication
#include <Adafruit_Sensor.h>    // Adafruit sensor library (optional, for unified sensor support)
#include <Adafruit_LSM9DS0.h>   // Adafruit LSM9DS0 sensor library
#include <MadgwickAHRS.h>
#include <Comms.h>
#include <Maths.h>

// Scale factors
#define X_SCALE_FACTOR 2.0f
#define G_SCALE_FACTOR 245.0f
#define M_SCALE_FACTOR 4.0f

// Thresholds
#define FREE_FALL_THRESHOLD 0.5f
#define IMPACT_THRESHOLD 2.5f
#define FALL_DURATION 200
#define ROLL_THRESHOLD 45.0f
#define PITCH_THRESHOLD 45.0f

// Declare extern variables (they are defined in your main file)
extern float ax, ay, az, at;
extern float gx, gy, gz;
extern float g_x, g_y, g_z;
extern float roll, pitch, yaw;

extern Adafruit_LSM9DS0 imu;
extern Madgwick filter;

#endif