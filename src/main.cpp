#include <Globals.h>
#include <LSM9DS0.h>


/**
 * Instances
 *
 */
// Create an instance of the LSM9DS0 class using I2C
Adafruit_LSM9DS0 imu = Adafruit_LSM9DS0();
Madgwick filter;

// filtered data
float ax, ay, az, at;   // accelerometer data
float gx, gy, gz;       // gyro data
float g_x, g_y, g_z;    // gravity vector

// filtered orientation
float roll, pitch, yaw;     // Euler angles


/**
 * Sensor Setup
 *
 */

// component ranges
void sensorSetup() {
    imu.setupAccel(Adafruit_LSM9DS0::LSM9DS0_ACCELRANGE_4G);
    imu.setupGyro(Adafruit_LSM9DS0::LSM9DS0_GYROSCALE_245DPS);
    imu.setupMag(Adafruit_LSM9DS0::LSM9DS0_MAGGAIN_2GAUSS);
}

// Setup function to initialize the IMU
void setup() {
    // Start serial communication
    Serial.begin(115200);

    // Wait for Serial to be ready (useful for some boards)
    while (!Serial) {}

    // Initialize the LSM9DS0 sensor
    if (!imu.begin()) {
        Serial.println("Failed to initialize LSM9DS0! Check your wiring.");
        while(true);  // Halt the program if the sensor isn't found
    }

    Serial.println("LSM9DS0 initialized successfully!");

    // setup sensor ranges
    sensorSetup();

    delay(1);
}

void loop() {
   getIMUData();
   delay(100);
}
