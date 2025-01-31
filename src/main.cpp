//#include <imu.h>
//#include <heartrate.h>

#define NO_SW_SERIAL
#include <Arduino.h>
#include <Adafruit_GPS.h>

#define BAUD_RATE 9600
#define GPS_SERIAL Serial1  // Set Serial1 for GPS functionality


// Connect GPS module to GPS Serial
Adafruit_GPS GPS(&GPS_SERIAL);

char nmeaSentence[100]; // buffer to store NMEA sentence
size_t nmea_index = 0;              // index for the buffer

void setup() {
    Serial.begin(115200);   // Initialises microcontroller
    Serial1.begin(9600);    // Initialises gps module

    if (GPS.begin(BAUD_RATE)) {
        Serial.print("Hardware Initialised");
    };

    GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCONLY);
    GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);
    GPS.sendCommand(PGCMD_ANTENNA);
}

void loop() {
    if (GPS.available()) {
        char c = GPS.read();

        if (c == '\n') {
            nmeaSentence[nmea_index] = '\0';    // creates a c-style string and allows print to terminal
            Serial.println(nmeaSentence);
            nmea_index = 0;
        } else {
            if (nmea_index < sizeof(nmeaSentence) - 1) {
                nmeaSentence[nmea_index] = c;
                nmea_index++;
            }
        }
    }
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
