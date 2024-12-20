//
// Created by Nathan on 10/10/2024.
//
#include <math.h>
#include "maths.h"

float convertAccData(uint16_t rawValue, float scaleFactor) {
    return (static_cast<float>(rawValue) / 32768.0f) * scaleFactor;
}

float convertGyroData(uint16_t rawValue, float scaleFactor) {
    return (static_cast<float>(rawValue) / 32768.0f) * scaleFactor;
}

float convertMagData(uint16_t rawValue, float scaleFactor) {
    return (static_cast<float>(rawValue) / 32768.0f) * scaleFactor;
}

float calcTotalAcc(float ax, float ay, float az) {
    return sqrtf(ax * ax + ay * ay + az * az);
}

void getGravityVector(float &gx, float &gy, float &gz, float q0, float q1, float q2, float q3) {
    gx = 2.0f * (q3 * q1 - q0 * q2);
    gy = 2.0f * (q0 * q1 + q2 * q3);
    gz = q0 * q0 - q1 * q1 - q2 * q2 + q3 * q3;
}

void getEulerAngles(float q0, float q1, float q2, float q3, float &roll, float &pitch, float &yaw) {
    roll = atan2f(2.0f * (q0 * q1 + q2 * q3), 1.0f - 2.0f * (q1 * q1 + q2 * q2));
    pitch = asinf(2.0f * (q0 * q2 - q3 * q1));
    yaw = atan2f(2.0f * (q0 * q3 + q1 * q2), 1.0f - 2.0f * (q2 * q2 + q3 * q3));
}


