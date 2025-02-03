//
// Created by Nathan on 21/10/2024.
//
#include "imu.h"
#include "components/imu/imu_conversion.h"    // For convertAccData, convertGyroData, getEulerAngles, etc.
#include "communication/comms.h"    // Include if needed for communication; remove if not required

// Static (internal) variables for IMU data
static Adafruit_LSM9DS0 imu = Adafruit_LSM9DS0();
static Madgwick filter;

// Raw and processed sensor data
static float ax, ay, az;
static float gx, gy, gz;
static float g_x, g_y, g_z;
static float roll, pitch, yaw;

// Initialize the IMU sensor
void setupIMU() {
    if (!imu.begin()) {
        Serial.println("Failed to initialize LSM9DS0! Check your wiring.");
        while (true);
    }
    Serial.println("LSM9DS0 initialized successfully!");

    // Set sensor ranges
    imu.setupAccel(Adafruit_LSM9DS0::LSM9DS0_ACCELRANGE_4G);
    imu.setupGyro(Adafruit_LSM9DS0::LSM9DS0_GYROSCALE_245DPS);
    imu.setupMag(Adafruit_LSM9DS0::LSM9DS0_MAGGAIN_2GAUSS);
}

// Update IMU data and print results
void updateIMUData() {
    // Read sensors
    imu.readAccel();
    imu.readGyro();

    // Convert readings
    ax = convertAccData(imu.accelData.x, X_SCALE_FACTOR);
    ay = convertAccData(imu.accelData.y, X_SCALE_FACTOR);
    az = convertAccData(imu.accelData.z, X_SCALE_FACTOR);

    gx = convertGyroData(imu.gyroData.x, G_SCALE_FACTOR);
    gy = convertGyroData(imu.gyroData.y, G_SCALE_FACTOR);
    gz = convertGyroData(imu.gyroData.z, G_SCALE_FACTOR);

    // Update filter with current readings
    filter.updateIMU(gx, gy, gz, ax, ay, az);

    // Get quaternion from filter
    float q0 = filter.getQ0();
    float q1 = filter.getQ1();
    float q2 = filter.getQ2();
    float q3 = filter.getQ3();

    // Compute gravity vector
    getGravityVector(g_x, g_y, g_z, q0, q1, q2, q3);

    // Compute linear acceleration
    float linear_ax = ax - g_x;
    float linear_ay = ay - g_y;
    float linear_az = az - g_z;

    // Compute orientation
    getEulerAngles(q0, q1, q2, q3, roll, pitch, yaw);

    // Fall detection logic
    float totalAccel = calcTotalAcc(linear_ax, linear_ay, linear_az);

    if (totalAccel < FREE_FALL_THRESHOLD) {
        Serial.println("Free-fall detected");
    }

    if (fabsf(roll) > ROLL_THRESHOLD) {
        Serial.println("Keep on Rolling Baby");
    }

    if (fabsf(pitch) > PITCH_THRESHOLD) {
        Serial.println("Pitch me Pitch me");
    }

    // Print data
    Serial.print(linear_ax); Serial.print(" ");
    Serial.print(linear_ay); Serial.print(" ");
    Serial.print(linear_az); Serial.print(" ");
    Serial.print(roll); Serial.print(" ");
    Serial.println(pitch);

    Serial.flush();
}

// Getter functions
float getRoll()  { return roll; }
float getPitch() { return pitch; }

