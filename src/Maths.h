//
// Created by Nathan on 10/10/2024.
//
#ifndef MATHS_H
#define MATHS_H

#include <stdint.h>

float convertAccData(uint16_t rawValue, float scaleFactor);
float convertGyroData(uint16_t rawValue, float scaleFactor);
float convertMagData(uint16_t rawValue, float scaleFactor);
float calcTotalAcc(float ax, float ay, float az);

void getGravityVector(float &gx, float &gy, float &gz, float q0, float q1, float q2, float q3);
void getEulerAngles(float q0, float q1, float q2, float q3, float &roll, float &pitch, float &yaw);

#endif // MATHS_H