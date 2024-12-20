//
// Created by Nathan on 3/11/2024.
//

/**
 * Determined in BPM
 *
 * Obtain raw signal
 * Convert analog to digital signal
 * - may be done on device? if not an ADC is required
 * Amplify and filter signal
 *
 *
 * static const int: use for constants that should not change and need to be shared across all instances or retained in a function.
 * static int: use for variables that need to retain their value between function calls or be shared among all class instances
*/

#include "heartrate.h"
#include <Arduino.h>

// Pin to which the heart rate sensor is connected
static const int heartSensorPin = A0;

// Parameters for peak detection
static float threshold = 218;
static unsigned long sampleInterval = 20;
static unsigned long lastSampleTime;

// Variables for heart rate calculation
static unsigned long lastBeatTime;
static unsigned long beatInterval;
static float bpm;
static bool beatDetected = false;
static int beatCount;
static float averageBPM;

// Printing timer
static unsigned long lastPrintTime;                         // time since last BPM print
                                                            // long because millis() is a long value
static const unsigned long printInterval = 30000;

// Smoothing variables
static const int smoothingWindow = 4;
static int readings[smoothingWindow];
static double bpmValues[smoothingWindow];
static int bpmIndex;
static int readIndex;
static int total;

float calculateAverageBPM() {
    float totalBPM = 0.0;
    for (double bpmValue : bpmValues) {
        totalBPM += bpmValue;
    }
    return totalBPM / smoothingWindow;
}

void getHeartRateData() {
    // only reads sample after interval
    if (millis() - lastSampleTime < sampleInterval) {
        return;
    }

    // takes timestamp of sample taken
    lastSampleTime = millis();

    // retrieves raw data from the device
    int rawValue = analogRead(heartSensorPin);

    // smoothing (rolling average)
    total -= readings[readIndex];                           // updates the running total by removing the oldest value
    readings[readIndex] = rawValue;                         // stores the new reading in the array
    total += readings[readIndex];                           // adds the new reading to the total
    readIndex = (readIndex + 1) % smoothingWindow;          // iterates through the array and wraps back one with smoothingWindow has been reached
    float smoothedValue = (float) total / smoothingWindow;  // calculates the smoothed value as the average

    Serial.print("Smoothed value: ");
    Serial.println(smoothedValue);

    // Peak Detection
    if (!beatDetected && smoothedValue > threshold) {
        beatDetected = true;
        beatInterval = millis() - lastBeatTime;             // millis() returns the number of milliseconds since the device was turned on
        beatCount +=1;
        lastBeatTime = millis();

        if (beatInterval > 0) {
//            bpm = 60000.0 / (float) beatInterval;
            bpmValues[bpmIndex] = 60000.0 / (float) beatInterval;
            bpmIndex = (bpmIndex + 1) % smoothingWindow;
        }
    }

//    Serial.print("Beat interval:  ");
//    Serial.println(beatInterval);
    Serial.print("Beat count:     ");
    Serial.println(beatCount);
    Serial.println();

    if (beatDetected && smoothedValue < threshold) {
        beatDetected = false;
    }

    // Print BPM every interval
    if (millis() - lastPrintTime >= printInterval) {
        lastPrintTime = millis();                           // resets the timer
        averageBPM = calculateAverageBPM();           // Calculate average BPM

        Serial.println();
        Serial.print("Average BPM: ");
        Serial.println(averageBPM, 1);                      // Print the average BPM to 1 decimal place
        Serial.println();

        beatCount = 0;
    }
}

