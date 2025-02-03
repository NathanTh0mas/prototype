//
// Created by Nathan on 20/12/2024.
//

/**
 *  Hardware vs Software Serial
 *  ----------------------------
 *  Hardware serial uses built in-UART GPIOs for serial communication
 *  Software serial emulates a serial port in software, allowing any GPIO pin for serial communication
 *
 *  Hardware serial is faster, more reliable and stable.
 *  Software serial allows for devices with limited UART pins to be used for serial comms,
 *  but can be unreliable for higher baud rates (>9600)
 *
 *
 *  Bit-banging
 *  ------------
 *  When using hardware serial ports the UART module (or other dedicated hardware peripherals) automatically
 *  generates the correct signal timings. "Bit-banging" is a software driven method of serial comms where the
 *  microcontroller manually controls the timing and transmission of data without dedicated hardware support.
 *  Software serial uses "bit-banging" to allow any GPIO to simulate a UART connection, at the cost of CPU processing.
 *
 *  Bit-banging is a software based method of sending serial data without hardware support.
 *
 *
 *  Arrow Operator (->)
 *  ------------------------
 *  When accessing members of an object instance the dot operator is used, however, when there is a pointer
 *  to an object the arrow operator is used. The arrow operand indicates that one is accessing a member
 *  function or variable from the object that the pointer refers to.
 *
 *
 *  Pointers and References
 *  -------------------------
 *  & is used to get the memory address of a variable.
 *	* is used to access the data stored at a given memory address via a pointer.
 *
 *
 *  String Literals
 *  ----------------
 * if string literals "" are used then a string is automatically null-terminated,
 * otherwise when entering characters using '' the '\0' null termination must be used
 *
 *
 * Orientation for Google Maps
 * ----------------------------
 * To get a location in google maps, from NMEA sentences, the lat and long, which are degrees-minutes,
 * must be converted to decimal-degrees
 *
 * Decimal degrees = Degrees + (Minutes/60)
 */

#include "gps.h"
#include <math.h>

/**
 * Points to an Adafruit_GPS object.
 * Using a pointer allows for the allocation of variable in memory heap but does not initialise the object
 * since the serial connection has not been setup i.e. serial1.begin(baud rate).
 */
Adafruit_GPS *GPS;

void setupGPS() {
    Serial.begin(115200);   // initialises serial comms with the microcontroller
    /**
     * Serial1 is mapped to RX1 (pin 19) and TX1 (pin 18) - Hardware Serial Ports
     * The GPS and microcontroller need to communicate at the same BAUD_RATE
     * This function allocates a buffer in RAM to store incoming data
     *
     * This function sets up the hardware serial (RX1 and TX1) at 9600 baud, enabling direct comms with the GPS module
     */
    GPS_SERIAL.begin(9600);    // Initialises serial comms with GPS module

    /**
     * Since the serial connection has been established with the GPS module,
     * a new object can be created and stored in the pointed memory allocation.
     *
     * new = dynamic allocation defers object creation until runtime.
     * This is useful when the object created is dependent on something else.
     *      i.e the gps module dependent on the serial comms being active.
     */
    GPS = new Adafruit_GPS(&GPS_SERIAL);

    /**
     * Initialises the hardware or software serial port
     * Returns True on successful hardware init
     */
    if (GPS->begin(BAUD_RATE)) {    // refer to top of script for arrow operator explanation
        Serial.print("Hardware Initialised");
    };

    /**
     * Send commands to determine which format of NMEA sentences are required
     */
    GPS->sendCommand(PMTK_SET_NMEA_OUTPUT_RMCONLY);

    /**
     * For the parsing code to work nicely and have time to sort through the data, and print it out,
     * Adafruit doesn't suggest using anything higher than 1 Hz
     */
    GPS->sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);

    GPS->sendCommand(PGCMD_ANTENNA);    // Request updates on antenna status
}

// Converts degrees to radians
double degreesToRadians(double degrees) {
    return degrees * M_PI / 180;
}

/**
 * Haversine Equation
 *
 * @param lat1 - current latitude
 * @param lon1 - current longitude
 * @param lat2 - safe zone latitude
 * @param lon2 - safe zone longitude
 * @return distance from safe zone
 */
double haversineDistance(double lat1, double lon1, double lat2, double lon2) {

    // Convert latitudes and longitudes from degrees to radians.
    double lat1Rad = degreesToRadians(lat1);
    double lat2Rad = degreesToRadians(lat2);
    double deltaLat = degreesToRadians(lat2 - lat1);
    double deltaLon = degreesToRadians(lon2 - lon1);

    // Compute haversine of the central angle
    double haversineAngle = sin(deltaLat / 2) * sin(deltaLat / 2) +
                            cos(lat1Rad) * cos(lat2Rad) *
                            sin(deltaLon / 2) * sin(deltaLon / 2);

    // computes central angle - angular distance between two points.
    double centralAngle =
            2 * atan2(sqrt(haversineAngle), sqrt(1 - haversineAngle));     // atan2 has numerical stability?

    // Compute distance between two points
    return EARTH_RADIUS * centralAngle;    // Arc length = radius * distance
}

/**
 *
 */
void monitoringSafeZone() {
    double currentLatitude = GPS->latitudeDegrees;
    double currentLongitude = GPS->longitudeDegrees;

    double distance = haversineDistance(currentLatitude, currentLongitude, safeZoneLatitude, safeZoneLongitude);

    Serial.print("Distance from safe zone: ");
    Serial.print(distance);
    Serial.println(" metres");
    Serial.println();

    if (distance > safeDistanceThreshold) {
        Serial.println("WARNING: Patient has left the safe zone");
    }
}

void loopGPS() {
    /**
     * GPS.available() checks if data is available (waiting to be read) within the buffer
     */
    while (GPS->available()) {
        /**
        * GPS.read() pulls data from the buffer
        */
        // char c = GPS->read();
        GPS->read();
        /**
         * GPS.parse() is a state-machine parser that processes incoming NMEA sentence data one char at a time.
         * states include - start detection, accumulation, end-of-sentence detection, tokenisation and validation
         * It stores the the tokenised sentence into variables (long, lat, alt, etc)
         */
        //GPS->parse(&c);
    }

    /**
     * GPS.NMEAreceived() returns true when a new complete NMEA sentence has been received and approved by GPS.parse()
     */
    if (GPS->newNMEAreceived()) {
        /**
         * GPS.lastNMEA() stores the entire last received NMEA sentence.
         */
        GPS->parse(GPS->lastNMEA());

        monitoringSafeZone();

        Serial.print("Current Latitude: ");
        Serial.println(GPS->latitudeDegrees, 4);

        Serial.print("Current Longitude: ");
        Serial.println(GPS->longitudeDegrees, 4);
        Serial.println();
    }
}