//
// Created by Nathan on 20/12/2024.
//

#include <Arduino.h>
#include <Adafruit_GPS.h>
#include <SoftwareSerial.h>

// Use Hardware Serial1 on Mega
Adafruit_GPS GPS(&Serial1);

void setup() {
    Serial.begin(115200);  // Serial monitor
    Serial1.begin(9600);   // GPS module on Serial1 (Mega's RX1, TX1)

    GPS.begin(9600);  // Initialize Adafruit GPS with the correct baud rate

    // OPTIONAL: Configure GPS update rate (1 Hz)
    GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);
    GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);

    Serial.println("GPS setup complete.");
}

void loop() {
    while (Serial1.available()) {
        char c = GPS.read();  // Read GPS data
        if (GPS.newNMEAreceived()) {
            if (GPS.parse(GPS.lastNMEA())) {  // Successfully parsed sentence
                Serial.print("Fix: "); Serial.println((int)GPS.fix);
                Serial.print("Satellites: "); Serial.println((int)GPS.satellites);
                Serial.print("Latitude: "); Serial.print(GPS.latitudeDegrees, 6);
                Serial.print(", Longitude: "); Serial.println(GPS.longitudeDegrees, 6);
            }
        }
    }
}