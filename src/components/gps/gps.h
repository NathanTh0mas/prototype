//
// Created by Nathan on 20/12/2024.
//

#ifndef PROTOTYPE_GPS_H
#define PROTOTYPE_GPS_H

#include <Arduino.h>
#include "Adafruit_GPS.h"

#define BAUD_RATE 9600                  // Max baud rate for GPS module
#define GPS_SERIAL Serial1              // Set Serial1 for GPS functionality
#define EARTH_RADIUS 6371000.0          // Earth's radius in metres

// Predefined safe zone coordinates.
const float safeZoneLatitude = -33.9009;
const float safeZoneLongitude = 151.1936;

// A threshold in meters.
const double safeDistanceThreshold = 25.0;

void setupGPS();

void loopGPS();

void convertToDecimalDegrees();

#endif //PROTOTYPE_GPS_H
