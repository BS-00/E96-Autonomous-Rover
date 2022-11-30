#include <Arduino.h>
#include "Drivetrain.h"

void Drivetrain::init(){
    pinMode(_frontEnA, OUTPUT);
    pinMode(_frontIn1, OUTPUT);
    pinMode(_frontIn2, OUTPUT);

    pinMode(_frontEnB, OUTPUT);
    pinMode(_frontIn3, OUTPUT);
    pinMode(_frontIn4, OUTPUT);

    pinMode(_backEnA, OUTPUT);
    pinMode(_backIn1, OUTPUT);
    pinMode(_backIn2, OUTPUT);

    pinMode(_backEnB, OUTPUT);
    pinMode(_backIn3, OUTPUT);
    pinMode(_backIn4, OUTPUT);
}

// Control ---------------------------------------------------

void Drivetrain::goForward(int speed){
    setFrontLeft(speed, true);
    setFrontRight(speed, true);
    setBackLeft(speed, true);
    setBackRight(speed, true);
}

void Drivetrain::goBackward(int speed){
    setFrontLeft(speed, false);
    setFrontRight(speed, false);
    setBackLeft(speed, false);
    setBackRight(speed, false);
}

void Drivetrain::turnLeft(int speed){
    // Set left side motors
    setFrontLeft(speed, false);
    setBackLeft(speed, false);

    // Set right side motors
    setFrontRight(speed, true);
    setBackRight(speed, true);
}

void Drivetrain::turnRight(int speed){
    // Set left side motors
    setFrontLeft(speed, true);
    setBackLeft(speed, true);

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
 * speed parameter (0 - 254) sets speed
 * direction parameter (true for forward, false for backward) sets rotation direction
 */
void Drivetrain::setFrontRight(int speed, bool direction){
    analogWrite(_frontEnA, speed);

    digitalWrite(_frontIn1, direction);
    digitalWrite(_frontIn2, !direction);
}

void Drivetrain::stopFrontRight(){
    setFrontRight(0, true);
}

/*
 * speed parameter (0 - 254) sets speed
 * direction parameter (true for forward, false for backward) sets rotation direction
 */
void Drivetrain::setFrontLeft(int speed, bool direction){
    analogWrite(_frontEnB, speed);

    digitalWrite(_frontIn3, direction);
    digitalWrite(_frontIn4, !direction);
}

void Drivetrain::stopFrontLeft(){
    setFrontLeft(0, true);
}


// Back Individual Control -----------------------------------------

/*
 * speed parameter (0 - 254) sets speed
 * direction parameter (true for forward, false for backward) sets rotation direction
 */
void Drivetrain::setBackLeft(int speed, bool direction){
    analogWrite(_backEnA, speed);

    digitalWrite(_backIn1, direction);
    digitalWrite(_backIn2, !direction);
}

void Drivetrain::stopBackLeft(){
    setBackLeft(0, true);
}

/*
 * speed parameter (0 - 254) sets speed
 * direction parameter (true for forward, false for backward) sets rotation direction
 */
void Drivetrain::setBackRight(int speed, bool direction){
    analogWrite(_backEnB, speed);

    digitalWrite(_backIn3, direction);
    digitalWrite(_backIn4, !direction);
}

void Drivetrain::stopBackRight(){
    setBackRight(0, true);
}
