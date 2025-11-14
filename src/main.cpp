#include <Arduino.h>
#include <Wire.h>
#include <ZumoShield.h>

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
void initializeRobot(){

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

  pinMode(LED, HIGH);
  initializeRobot();
}

// Define Robot Behavior
void loop(){
  getReflectiveSensor();
  getSerialInput();

}