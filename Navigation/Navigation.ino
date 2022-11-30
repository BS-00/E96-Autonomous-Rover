#include "gyroscope.h"
#include "ultrasonic.h"
#include "rover.h"
#include "Drivetrain.h"
#include "constants.h"


// to keep track of our current position in centimeters from starting point
int distX = 0;
int distY = 0;
const float originalYaw = 0.0;

UltSonSr sensorFrontCenter(47, 46);
UltSonSr sensorFrontLeft(23, 22);
UltSonSr sensorFrontRight(49, 48);
UltSonSr sensorLeft(43, 42);
UltSonSr sensorRight(51, 50);
UltSonSr sensorBack(45, 44);
Drivetrain drive;
Rover bruver;


void setup() {
  Serial.begin(9600);
  Wire.begin();
  gyroSetup();
  

}

void loop() {

  //while we're in the obstacle area, keep traveling forward and avoiding obstacles
  while (distX <= STRAIGHTAWAYLEN) {
    moveForwardUntilBlocked();
    maneuverAround();
    
  }

  //we are now in the search area
  //first, we need to make sure the rover is pointing straight ahead. Turn right until we are within -2 to +2 yaw
  while ((((int)getYaw() % 360) < (originalYaw - 2)) || (((int)getYaw() % 360) < (originalYaw + 2))) {
    drive.turnRight(SPEED);
  }
  drive.halt();
  
  //make sure we're in the search area
  while ((sensorFrontCenter.distToNearestObj() > 80) || ((sensorLeft.distToNearestObj() + sensorRight.distToNearestObj() + ROVERWIDTH) < 90)) {
    drive.goForward(SPEED);
  }
  drive.halt();


  //OKAY, SO for the search part of the algorithm, I have pseudocode but haven't finished writing the actual code yet

  if ((sensorFrontCenter.distToNearestObj() < 80)) {
    //the object must be in view of the front sensor, so try to go over and pick it up
  } else if ((sensorLeft.distToNearestObj() + sensorRight.distToNearestObj() + ROVERWIDTH) < 90) {
    //the object must be in view of one of the side sensors. determine which one by moving forward and comparing distances, then go try to pick it up
  }



}


void moveForwardUntilBlocked() {
  
  int t = millis(); 

  //if there's no obstacle in front of the rover within 10 cm, keep moving forward
  while (!sensorFrontCenter.isImmediatelyBlocked()){
    drive.goForward(SPEED);
  }
  drive.halt();
  updateRoverPos(t);
}


void updateRoverPos(int startTime) {
  //to keep track of the position, we calculate how far the rover just moved and update the position vars
  int t = millis() - startTime;
  int distanceTraveled = t * SPEED;
  if (bruver.orientation == FORWARD) {
    distX += distanceTraveled;
  } else if (bruver.orientation == RIGHT) {
    distY += distanceTraveled;
  } else if (bruver.orientation == LEFT) {
    distY -= distanceTraveled;
  } else {distX -= distanceTraveled;}
}



void makeLeftTurn() {
  int desiredYaw = (getYaw() + 90); 
  while (getYaw() < (desiredYaw - 2)) { //the - 2 is to give some room for error
    drive.turnLeft(SPEED);
  }
  drive.halt();
  switch (bruver.orientation) {
    case FORWARD:
      bruver.orientation = LEFT;
      break;
    case LEFT:
      bruver.orientation = BACKWARD;
      break;
    case BACKWARD:
      bruver.orientation = RIGHT;
      break;
    default:
      bruver.orientation = FORWARD;
      break;
  } 
}

void makeRightTurn() {
  int desiredYaw = (getYaw() - 90); 
  while (getYaw() > (desiredYaw + 2)) { //the + 2 is to give some room for error
    drive.turnRight(SPEED);
  }
  drive.halt();
  switch (bruver.orientation) {
    case FORWARD:
      bruver.orientation = RIGHT;
      break;
    case RIGHT:
      bruver.orientation = BACKWARD;
      break;
    case BACKWARD:
      bruver.orientation = LEFT;
      break;
    default:
      bruver.orientation = FORWARD;
      break;
  }
}


void maneuverAround() {

  if (sensorRight.isClear()) {

    int t = millis();    
    makeRightTurn();
    if (!sensorLeft.isClear()){
      moveForwardUntilBlocked();
    }
    drive.halt();
    updateRoverPos(t);
    makeLeftTurn();
    drive.halt();

  } else if (sensorLeft.isClear()) {

    int t = millis();
    makeLeftTurn();
    if (!sensorRight.isClear()){
      moveForwardUntilBlocked();
    }
    drive.halt();
    updateRoverPos(t);
    makeRightTurn();
    drive.halt();    
  }

}


/*
#include "Drivetrain.h"
#include "constants.h"

Drivetrain drive;

void setup() {

}

void loop() {
  
  drive.goForward(SPEED);
  delay(2000);
  drive.stop();
  delay(2000);  
}
*/
