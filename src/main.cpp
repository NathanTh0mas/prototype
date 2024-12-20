#include <imu.h>
#include <heartrate.h>

// Setup function to initialize the IMU
void setup() {
    // Start serial communication
    Serial.begin(115200);

    // Wait for Serial to be ready (useful for some boards)
    while (!Serial) {}

    // setup sensor ranges
    setupIMU();
    setupHeartRateSensor();

    delay(1);
}

void loop() {
   updateIMUData();
   getHeartRateData();
   delay(100);
}
