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
*/

#include "heartrate.h"
#include <Arduino.h>

// Pin to which the heart rate sensor is connected
static const int heartSensorPin = A0;

// Adjustable parameters for peak detection
// Tweak these values based on your sensor's output
static float threshold = 520;
static unsigned long sampleInterval = 20;
static unsigned long lastSampleTime = 0;

// Variables for heart rate calculation
static unsigned long lastBeatTime = 0;
static unsigned long beatInterval = 0;
static float bpm = 0;
static bool beatDetected = false;

// Optional: Smoothing variables
static const int smoothingWindow = 4;
static int readings[smoothingWindow];
static int readIndex = 0;
static int total = 0;

void setupHeartRateSensor() {
    // Initialize the smoothing array
    for (int i = 0; i < smoothingWindow; i++) {
        readings[i] = 0;
    }

    // If needed, you could do additional sensor setup here
    // (e.g., pinMode(heartSensorPin, INPUT) if required)
}

void getHeartRateData() {
    // Check if it’s time to sample
    if (millis() - lastSampleTime < sampleInterval) {
        return; // Not time yet, so return early
    }
    lastSampleTime = millis();

    int rawValue = analogRead(heartSensorPin);

    // Smoothing (rolling average)
    total -= readings[readIndex];
    readings[readIndex] = rawValue;
    total += readings[readIndex];
    readIndex = (readIndex + 1) % smoothingWindow;
    float smoothedValue = (float)total / smoothingWindow;

    // Detect peaks
    if (!beatDetected && smoothedValue > threshold) {
        beatDetected = true;
        beatInterval = millis() - lastBeatTime;
        lastBeatTime = millis();

        if (beatInterval > 0) {
            bpm = 60000.0 / (float)beatInterval;
        }
        Serial.print("Heartbeat detected! BPM: ");
        Serial.println(bpm, 1);
    }

    if (beatDetected && smoothedValue < threshold) {
        beatDetected = false;
    }
}