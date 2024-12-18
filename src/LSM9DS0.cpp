//
// Created by Nathan on 21/10/2024.
//
#include <Adafruit_LSM9DS0.h>   // Adafruit LSM9DS0 sensor library
#include <MadgwickAHRS.h>
#include <Maths.h>
#include <Globals.h>
#include <LSM9DS0.h>

/**
 * Instances
 *
 */
// Create an instance of the LSM9DS0 class using I2C
Adafruit_LSM9DS0 imu = Adafruit_LSM9DS0();
Madgwick filter;

void getIMUData(){
    // Read individual sensor data
    imu.readAccel();      // Reads the accelerometer data and stores it in accelData structure
    imu.readGyro();       // Reads the gyroscope data and stores it in gyroData structure

    ax = convertAccData(imu.accelData.x, X_SCALE_FACTOR);
    ay = convertAccData(imu.accelData.y, X_SCALE_FACTOR);
    az = convertAccData(imu.accelData.z, X_SCALE_FACTOR);
//    at = totalAcc(ax, ay, az);

    gx = convertGyroData(imu.gyroData.x, G_SCALE_FACTOR);
    gy = convertGyroData(imu.gyroData.y, G_SCALE_FACTOR);
    gz = convertGyroData(imu.gyroData.z, G_SCALE_FACTOR);
//    gt = totalGyro(gx, gy, gz);

    // Update Madgwick filter with converted imu data
    filter.updateIMU(gx, gy, gz, ax, ay, az);

    // Access quaternions
    float q0 = filter.getQ0();
    float q1 = filter.getQ1();
    float q2 = filter.getQ2();
    float q3 = filter.getQ3();

    // determine gravity vector
    getGravityVector(g_x, g_y, g_z, q0, q1, q2, q3);

    // compute linear acceleration
    float linear_ax = ax - g_x;
    float linear_ay = ay - g_y;
    float linear_az = az - g_z;

    // compute roll and pitch
    getEulerAngles(q0, q1, q2, q3, roll, pitch, yaw);

    // Fall detection logic
    float totalAccel = calcTotalAcc(linear_ax, linear_ay, linear_az);

    if (totalAccel < FREE_FALL_THRESHOLD) {
        Serial.println("Free-fall detected");
    }

    if (abs(roll) > ROLL_THRESHOLD) {
        Serial.println("Keep on Rolling Baby");
    }

    if (abs(pitch) > PITCH_THRESHOLD) {
        Serial.println("Pitch me Pitch me");
    }

    Serial.print(linear_ax), Serial.print(" ");
    Serial.print(linear_ay), Serial.print(" ");
    Serial.print(linear_az), Serial.print(" ");
    Serial.print(roll), Serial.print(" ");
    Serial.println(pitch);

    Serial.flush();
}