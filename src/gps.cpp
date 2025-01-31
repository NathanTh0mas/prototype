//
// Created by Nathan on 20/12/2024.
//

/**
 *  Hardware serial uses built in-UART GPIOs for serial communication
 *  Software serial emulates a serial port in software, allowing any GPIO pin for serial communication
 *
 *  Hardware serial is faster, more reliable and stable.
 *  Software serial allows for devices with limited UART pins to be used for serial comms,
 *  but can be unreliable for higher baud rates (>9600)
 *
 *  When using hardware serial ports the UART module (or other dedicated hardware peripherals) automatically
 *  generates the correct signal timings. "Bit-banging" is a software driven method of serial comms where the
 *  microcontroller manually controls the timing and transmission of data without dedicated hardware support.
 *  Software serial uses "bit-banging" to allow any GPIO to simulate a UART connection, at the cost of CPU processing.
 *
 *  Bit-banging is a software based method of sending serial data without hardware support.
 */

//
//
//#include <Arduino.h>
//#include <Adafruit_GPS.h>
//
//#define BAUD_RATE 9600
//#define GPS_SERIAL Serial1  // Set Serial1 for GPS functionality
//
//// Connect GPS module to GPS Serial
//Adafruit_GPS GPS(&GPS_SERIAL);
//
//char nmeaSentence[100]; // buffer to store NMEA sentence
//size_t nmea_index = 0;              // index for the buffer
//
//void setup() {
//
//    /**
//     * Serial1 is mapped to RX1 (pin 19) and TX1 (pin 18) - Hardware Serial Ports
//     * The GPS and microcontroller need to communicate at the same BAUD_RATE
//     * This function allocates a buffer in RAM to store incoming data
//     *
//     * This function sets up the hardware serial (RX1 and TX1) at 9600 baud, enabling direct comms with the GPS module
//     */
//    Serial1.begin(9600);    // Initialises
//
//    /**
//     * Initialises the hardware or software serial port
//     * Returns True on successful hardware init
//     */
//    if (GPS.begin(BAUD_RATE)) {
//        Serial.print("Hardware Initialised");
//    };
//
//    /**
//     * Send commands to determine which format of NMEA sentences are required
//     */
//    GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCONLY);
//
//    /**
//     * For the parsing code to work nicely and have time to sort through the data, and print it out,
//     * Adafruit doesn't suggest using anything higher than 1 Hz
//     */
//    GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);
//
//    // Request updates on antenna status
//    GPS.sendCommand(PGCMD_ANTENNA);
//
//}
//
///**
// * GPS.read()
// * GPS.newNMEAreceived() -  new data received?
// * GPS.parse(GPS.lastNMEA())
// * GPS.available() - How many bytes are available to read
// * GPS.write() - sends a byte of data to the GPS module
// */
//
//void loop() {
///**
// * GPS.read() must be called frequently or the buffer may overflow
// * Common approach is to use a char buffer to hold an entire sentence, read char until "\n" is presented
// * NMEA sentence is 82 char long
// * call newNMEAreceived() after, at least, every 10 calls
// */
//    if (GPS.available()) {
//        char c = GPS.read();
//
//        /**
//         * if string literals "" are used then the string is automatically null-terminated,
//         * otherwise when entering characters using '' the '\0' null termination must be used
//         */
//        if (c == '\n') {
//            nmeaSentence[nmea_index] = '\0';    // creates a c-style string and allows print to terminal
//            Serial.println(nmeaSentence);
//            nmea_index = 0;
//        } else {
//            if (nmea_index < sizeof(nmeaSentence) - 1) {
//                nmeaSentence[nmea_index] = c;
//                nmea_index++;
//            }
//        }
//    }
//}
//
