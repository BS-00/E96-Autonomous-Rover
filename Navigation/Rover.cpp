#include <Arduino.h>
#include "Rover.hpp"
#include "src/Constants.hpp"

bool Rover::init () {
  sensorFCenter.init(47, 46);
  sensorFL.init(23, 22);
  sensorFR.init(49, 48);
  sensorL.init(43, 42);
  sensorR.init(51, 50);
  sensorBack.init(45, 44);

  drive.init();
  gyro.init();
  assem.init(110, 90);

  _originalYaw = gyro.yaw();
}

void Rover::avoidObstacle () {
  if (sensorR.hasSpace()) { 
    turn(LEFT);
    
    int t = millis();   
    drive.goForward(SPEED);
    for (;;) if (!sensorL.isBLocked()) break;
    delay(AVOIDDELAY);
    
    drive.halt();
    _updatePos(t);
    
    turn(LEFT);
  } 
  else if (sensorL.hasSpace()) {
    turn(RIGHT);
    
    int t = millis();
    drive.goForward(SPEED);
    for (;;) if (!sensorR.isBLocked()) break;
    delay(AVOIDDELAY);
    
    drive.halt();
    _updatePos(t);
    
    turn(RIGHT); 
  }

}

//MAKE CODE LOOK BETTER V
//Only accepts left and right
void Rover::turn (Direction dir) {
  if (dir == LEFT) {
	  //int desiredYaw = (gyro.yaw() + 90); 
	  drive.turnLeft(SPEED);
	  /*while (((int)getYaw() % 360) < (desiredYaw - 1)) { //the + 2 is to give some room for error
		continue;
	  }*/
	  delay(TURNDELAY);
	  drive.halt();
	  switch (orientation) {
      case FORWARD:
        orientation = LEFT;
        break;
      case LEFT:
        orientation = BACKWARD;
        break;
      case BACKWARD:
        orientation = RIGHT;
        break;
      default:
        orientation = FORWARD;
        break;
	  } 
  } else if (dir == RIGHT) {
    //int desiredYaw = (gyro.yaw() - 90); 
    drive.turnRight(SPEED);
    /*while (((int)getYaw() % 360) > (desiredYaw + 1)) { //the + 2 is to give some room for error
    continue;
    }*/
    delay(TURNDELAY);
    drive.halt();
    switch (orientation) {
      case FORWARD:
        orientation = RIGHT;
        break;
      case RIGHT:
        orientation = BACKWARD;
        break;
      case BACKWARD:
        orientation = LEFT;
        break;
      default:
        orientation = FORWARD;
        break;
    }
  }
}

void Rover::forwardUntilBlocked () {
  int t = millis(); 
  drive.goForward(SPEED);
  
  for (;;) {
    if (
      sensorFCenter.isBLocked() ||
      (sensorFR.isBLocked() && !sensorR.isBLocked()) ||
      (sensorFL.isBLocked() && !sensorL.isBLocked())
    ) break;

    //Stops the rover from running into walls
    if (sensorL.isBLocked()) {
      turn(RIGHT);
      for (;;) if (!sensorBack.isBLocked()) break;
      turn(LEFT);
    } else if (sensorR.isBLocked()) {
      turn(LEFT);
      for (;;) if (!sensorBack.isBLocked()) break;
      turn(RIGHT);
    }
  }
  
  drive.halt();
  _updatePos(t);
}

void Rover::grab () {
  assem.set_rotation(ClawAssembly::CLAW, 0);
  assem.set_rotation(ClawAssembly::TILT, 90+TILTAMOUNT);
}

void Rover::_updatePos (int startTime) {
  //to keep track of the position, we calculate how far the rover just moved and update the position vars
  //FIX THIS CALCULATION
  int t = millis() - startTime;
  int distanceTraveled = t * SPEED;
  if (orientation == FORWARD) {
    _xPosCm += distanceTraveled;
  } 
  else if (orientation == RIGHT) {
    _yPosCm += distanceTraveled;
  } 
  else if (orientation == LEFT) {
    _yPosCm -= distanceTraveled;
  } 
  else {
    _xPosCm -= distanceTraveled;
  }
}

int Rover::xPosCm () const {
  return _xPosCm;
}

int Rover::yPosCm () const {
  return _yPosCm;
}