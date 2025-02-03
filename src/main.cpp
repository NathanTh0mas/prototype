//#include <imu.h>
//#include <heartrate.h>


#include <Arduino.h>
#include "components/gps/gps.h"

void setup() {
    setupGPS();
}

void loop() {
    loopGPS();
}


//static const int heartSensorPin = A0;
//
//// Setup function to initialize the IMU
//void setup() {
//    // Start serial communication
//    Serial.begin(115200);
//
//    // Wait for Serial to be ready (useful for some boards)
//    while (!Serial) {}
//
//    // setup sensor ranges
//    // setupIMU();
//    delay(1);
//}
//
//void loop() {
//    int rawValue = analogRead(heartSensorPin);
//
//        if (millis() > 3000) {
//            Serial.print("Raw value:      ");
//            Serial.println(rawValue);
//            getHeartRateData();
//        }
//
//        // updateIMUData();
//        delay(100);
//}
