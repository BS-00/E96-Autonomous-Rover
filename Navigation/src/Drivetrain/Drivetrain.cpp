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

// Control ---------------------------------------------------

void Drivetrain::goForward(int speed){
    setFrontLeft(speed+DRIFTCOMPENSATION, true);
    setFrontRight(speed, true);
    setBackLeft(speed+DRIFTCOMPENSATION, true);
    setBackRight(speed, true);
}

void Drivetrain::goBackward(int speed){
    setFrontLeft(speed+DRIFTCOMPENSATION, false);
    setFrontRight(speed, false);
    setBackLeft(speed+DRIFTCOMPENSATION, false);
    setBackRight(speed, false);
}

void Drivetrain::turnLeft(int speed){
    // Set left side motors
    setFrontLeft(speed+DRIFTCOMPENSATION, false);
    setBackLeft(speed+DRIFTCOMPENSATION, false);

    // Set right side motors
    setFrontRight(speed, true);
    setBackRight(speed, true);
}

void Drivetrain::turnRight(int speed){
    // Set left side motors
    setFrontLeft(speed+DRIFTCOMPENSATION, true);
    setBackLeft(speed+DRIFTCOMPENSATION, true);

    // Set right side motors
    setFrontRight(speed, false);
    setBackRight(speed, false);
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
