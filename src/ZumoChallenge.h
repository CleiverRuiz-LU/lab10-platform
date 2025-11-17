#ifndef ZUMO_CHALLENGE_H
#define ZUMO_CHALLENGE_H

#include <Arduino.h>
#include <ZumoShield.h>

// ========== CONSTANTS ==========
#define LED 13
#define QTR_THRESHOLD     1500
#define REVERSE_SPEED     200
#define TURN_SPEED        200
#define FORWARD_SPEED     200
#define REVERSE_DURATION  200
#define TURN_DURATION     300
#define NUM_SENSORS       6

// ========== EXTERNAL OBJECTS ==========
extern ZumoBuzzer buzzer;
extern ZumoMotors motors;
extern Pushbutton button;
extern ZumoReflectanceSensorArray sensors;
extern unsigned int sensor_values[NUM_SENSORS];

// ========== FUNCTION DECLARATIONS ==========

void RobotInitialize() {
  digitalWrite(LED, HIGH);  
  button.waitForButton();    
  digitalWrite(LED, LOW);    

  // Countdown "beeps"
  for (int i = 0; i < 3; i++) {
    delay(1000);
    buzzer.playNote(NOTE_G(3), 200, 15);
  }

  // "GO!" beep
  delay(1000);
  buzzer.playNote(NOTE_G(4), 500, 15);
  delay(1000);
}

unsigned int* getReflectanceSensor() {
  sensors.read(sensor_values);
  return sensor_values;
}

void showReflectanceSensor() {
  Serial.print("Sensors: ");
  for (int i = 0; i < NUM_SENSORS; i++) {
    Serial.print(sensor_values[i]);
    if (i < NUM_SENSORS - 1)
      Serial.print(", ");
  }
  Serial.println();
}

#endif
