//
// Created by Nathan on 10/10/2024.
//

#include <stdint.h>
#include <math.h>
#include "Maths.h"

/**
 * IMU
 */


/**
 *
 * @param rawValue
 * @param scaleFactor
 * @return
 */
float convertAccData(uint16_t rawValue, float scaleFactor) {
    return (static_cast<float>(rawValue) / 32768.0f) * scaleFactor;
}

/**
 *
 * @param rawValue
 * @param scaleFactor
 * @return
 */
float convertGyroData(uint16_t rawValue, float scaleFactor) {
    return (static_cast<float>(rawValue) / 32768.0f) * scaleFactor;
}

/**
 *
 * @param rawValue
 * @param scaleFactor
 * @return
 */
float convertMagData(uint16_t rawValue, float scaleFactor) {
    return (static_cast<float>(rawValue) / 32768.0f) * scaleFactor;
}

/**
 *
 * @param ax
 * @param ay
 * @param az
 * @return
 */
float calcTotalAcc(float ax, float ay, float az) {
    return sqrtf(ax * ax + ay * ay + az * az);
}


/**
 * Calculating the gravity vector
 * global gravity vector (0,0,-1)
 * components of the gravity vector in the local frame
 * @param gx
 * @param gy
 * @param gz
 * quaternion elements
 * @param q0
 * @param q1
 * @param q2
 * @param q3
 */

void getGravityVector(float &gx, float &gy, float &gz, float q0, float q1, float q2, float q3) {
    gx = 2 * (q3 * q1 - q0 * q2);
    gy = 2 * (q0 * q1 + q2 * q3);
    gz = q0 * q0 - q1 * q1 - q2 * q2 + q3 * q3;
}

/**
 * Convert quaternions to Euler angles
 * @param q0
 * @param q1
 * @param q2
 * @param q3
 * @param roll = arctan2(2(q0q1+q2q3), 1-2(q1^2 + q2^2))
 * @param pitch = arcsin(2(q0q2 - q3 q1))
 * @param yaw = arctan2(2(q0q3+q1q2), 1-2(q2^2+q3^2))
 */
void getEulerAngles(float q0, float q1, float q2, float q3, float &roll, float &pitch, float &yaw) {
    roll = atan2f(2.0f * (q0 * q1 + q2 * q3), 1.0f - 2.0f * (q1 * q1 + q2 * q2));
    pitch = asinf(2.0f * (q0 * q2 - q3 * q1));
    yaw = atan2f(2.0f * (q0 * q3 + q1 * q2), 1.0f - 2.0f * (q2 * q2 + q3 * q3));
}

/**
 * HEART
 */

/**
 *
 * @param beatCount
 * @param intervalMs
 * @return
 */
// BPM Calculation Function
float calculateBPM(int beatCount, int intervalMs) {
    float bpm = (beatCount / (intervalMs / 1000.0)) * 60.0;
    return bpm;
}


/**
 * More efficient to count bpm over a shorter time period (e.g. 10s - 15s)
 * @param beats
 * @param timePeriod
 * @return beats per minute
 */
float getBeatsPerMinute(float numberOfBeats, float setTimePeriod) {
    return (numberOfBeats * 60) / setTimePeriod;
}