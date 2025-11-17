#include <Arduino.h>
#include <Wire.h>
#include <ZumoShield.h>
#include "ZumoChallenge.h"

#define LED 13                  // I/O Yellow LED 
#define QTR_THRESHOLD     1500  // microseconds
#define REVERSE_SPEED     200   // 0 is stopped, 400 is full speed
#define TURN_SPEED        200
#define FORWARD_SPEED     200
#define REVERSE_DURATION  200 // ms
#define TURN_DURATION     300 // ms
#define NUM_SENSORS       6

// Initialize Zumo
ZumoBuzzer buzzer;
ZumoMotors motors;
Pushbutton button(ZUMO_BUTTON);             // Start Zumo - pushbutton on pin 12
unsigned int sensor_values[NUM_SENSORS];    // Define # of Sensors or Eyes
ZumoReflectanceSensorArray sensors(QTR_NO_EMITTER_PIN); // Initialize Reflectance Sensors


// Push Button
void waitForButtonAndCountDown(){

  // Initialize CountDown
  digitalWrite(LED, HIGH);  // Turn Yellow LED ON
  button.waitForButton();   // Wait for Button on Pin 12
  digitalWrite(LED, LOW);   // Turn Yellow LED OFF

  // Play CountDown Sound
  for (int i = 0; i < 3; i++){
    delay(1000);
    buzzer.playNote(NOTE_G(3), 200, 15);
  }

  // Play GO! Sound
  delay(1000);
  buzzer.playNote(NOTE_G(4), 500, 15);
  delay(1000);
}

// Define workspace
void setup(){

  pinMode(LED, OUTPUT);  
  Serial.begin(9600);

  Serial.println("Press button to start...");
  waitForButtonAndCountDown();

  Serial.println("Reading reflectance sensors...");
}

// Define Robot Behavior
void loop(){

  // Read from Reflectance Eye Sensors
  sensors.read(sensor_values);
  showReflectanceSensor();

  // Check for Button Press (Emergency Stop)
  if (button.isPressed()){
    motors.setSpeeds(0, 0);
    button.waitForRelease();
    waitForButtonAndCountDown();
  }

  if (sensor_values[0] > QTR_THRESHOLD){
    // if leftmost sensor detects line, reverse and turn to the right
    motors.setSpeeds(-REVERSE_SPEED, -REVERSE_SPEED);
    delay(REVERSE_DURATION);
    motors.setSpeeds(TURN_SPEED, -TURN_SPEED);
    delay(TURN_DURATION);
    motors.setSpeeds(FORWARD_SPEED, FORWARD_SPEED);
  }
  else if (sensor_values[5] > QTR_THRESHOLD){
    // if rightmost sensor detects line, reverse and turn to the left
    motors.setSpeeds(-REVERSE_SPEED, -REVERSE_SPEED);
    delay(REVERSE_DURATION);
    motors.setSpeeds(-TURN_SPEED, TURN_SPEED);
    delay(TURN_DURATION);
    motors.setSpeeds(FORWARD_SPEED, FORWARD_SPEED);
  }
  else{
    // otherwise, go straight
    motors.setSpeeds(FORWARD_SPEED, FORWARD_SPEED);
  }

}