#include <Arduino.h>
#include "Drivetrain.hpp"
#include "../Constants.hpp"

void Drivetrain::init(){
  pinMode(FRONTENA, OUTPUT);
  pinMode(FRONTIN1, OUTPUT);
  pinMode(FRONTIN2, OUTPUT);

  pinMode(FRONTENB, OUTPUT);
  pinMode(FRONTIN3, OUTPUT);
  pinMode(FRONTIN4, OUTPUT);

  pinMode(BACKENA, OUTPUT);
  pinMode(BACKIN1, OUTPUT);
  pinMode(BACKIN2, OUTPUT);

  pinMode(BACKENB, OUTPUT);
  pinMode(BACKIN3, OUTPUT);
  pinMode(BACKIN4, OUTPUT);
}

// Helper -----

//Cuts off any speeds not within the range MIN_MOTOR_SPEED - MAX_MOTOR_SPEED
void Drivetrain::ensureValidSpeed(int& speed) {
  speed = min(speed, MOTOR_MAX_SPEED);
  speed = max(speed, MOTOR_MIN_SPEED);
}

// Control ---------------------------------------------------

void Drivetrain::forward(int lSpeed, int rSpeed) {  
  if (DRIFT_TOWARD_LEFT) rSpeed -= DRIFT_COMPENSATION;
  else lSpeed -= DRIFT_COMPENSATION;
  
  ensureValidSpeed(lSpeed);
  ensureValidSpeed(rSpeed);
  
  setFrontLeft(lSpeed, true);
  setFrontRight(rSpeed, true);
  setBackLeft(lSpeed, true);
  setBackRight(rSpeed, true);
}

void Drivetrain::backward(int lSpeed, int rSpeed){  
  if (DRIFT_TOWARD_LEFT) rSpeed -= DRIFT_COMPENSATION;
  else lSpeed -= DRIFT_COMPENSATION;
  
  ensureValidSpeed(lSpeed);
  ensureValidSpeed(rSpeed);

  setFrontLeft(lSpeed, false);
  setFrontRight(rSpeed, false);
  setBackLeft(lSpeed, false);
  setBackRight(rSpeed, false);
}

void Drivetrain::turnLeft(int speed) {
  int lSpeed = speed, rSpeed = speed;
  
  if (DRIFT_TOWARD_LEFT) rSpeed -= DRIFT_COMPENSATION;
  else lSpeed -= DRIFT_COMPENSATION;
  
  ensureValidSpeed(lSpeed);
  ensureValidSpeed(rSpeed);

  // Set left side motors
  setFrontLeft(lSpeed, false);
  setBackLeft(lSpeed, false);

  // Set right side motors
  setFrontRight(rSpeed, true);
  setBackRight(rSpeed, true);
}

void Drivetrain::turnRight(int speed) {
  int lSpeed = speed, rSpeed = speed;
  
  if (DRIFT_TOWARD_LEFT) rSpeed -= DRIFT_COMPENSATION;
  else lSpeed -= DRIFT_COMPENSATION;
  
  ensureValidSpeed(lSpeed);
  ensureValidSpeed(rSpeed);

  // Set left side motors
  setFrontLeft(lSpeed, true);
  setBackLeft(lSpeed, true);

  // Set right side motors
  setFrontRight(rSpeed, false);
  setBackRight(rSpeed, false);
}

void Drivetrain::halt(){
  stopFrontLeft();
  stopFrontRight();
  stopBackLeft();
  stopBackRight();
}

// Individual Control

// Front Individual Control ---------------------------------------

/*
 * speed parameter (0 - 255) sets speed
 * direction parameter (true for forward, false for backward) sets rotation direction
 */
void Drivetrain::setFrontRight(int speed, bool direction){
  analogWrite(FRONTENA, speed);

  digitalWrite(FRONTIN1, direction);
  digitalWrite(FRONTIN2, !direction);
}

void Drivetrain::stopFrontRight(){
  setFrontRight(0, true);
}

/*
 * speed parameter (0 - 255) sets speed
 * direction parameter (true for forward, false for backward) sets rotation direction
 */
void Drivetrain::setFrontLeft(int speed, bool direction){
  analogWrite(FRONTENB, speed);

  digitalWrite(FRONTIN3, direction);
  digitalWrite(FRONTIN4, !direction);
}

void Drivetrain::stopFrontLeft(){
  setFrontLeft(0, true);
}


// Back Individual Control -----------------------------------------

/*
 * speed parameter (0 - 255) sets speed
 * direction parameter (true for forward, false for backward) sets rotation direction
 */
void Drivetrain::setBackLeft(int speed, bool direction){
  analogWrite(BACKENA, speed);

  digitalWrite(BACKIN1, direction);
  digitalWrite(BACKIN2, !direction);
}

void Drivetrain::stopBackLeft(){
  setBackLeft(0, true);
}

/*
 * speed parameter (0 - 255) sets speed
 * direction parameter (true for forward, false for backward) sets rotation direction
 */
void Drivetrain::setBackRight(int speed, bool direction){
  analogWrite(BACKENB, speed);

  digitalWrite(BACKIN3, direction);
  digitalWrite(BACKIN4, !direction);
}

void Drivetrain::stopBackRight(){
  setBackRight(0, true);
}