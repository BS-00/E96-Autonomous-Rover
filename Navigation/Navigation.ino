#include "gyroscope.h"
#include "ultrasonic.h"
#include "rover.h"
#include "Drivetrain.h"
#include "constants.h"
#include "Mechanism.hpp"


// to keep track of our current position in centimeters from starting point
const float originalYaw = 0.0;

UltSonSr sensorFrontCenter(47, 46);
UltSonSr sensorFrontLeft(23, 22);
UltSonSr sensorFrontRight(49, 48);
UltSonSr sensorLeft(43, 42);
UltSonSr sensorRight(51, 50);
UltSonSr sensorBack(45, 44);
Drivetrain drive;
Rover bruver;
Mechanism m = Mechanism(2, 3);


void setup() {
  Serial.begin(9600);
  Wire.begin();
  gyroSetup();
  m.init(110, 90);
}

void moveForwardUntilBlocked() {
  //if there's no obstacle in front of the rover within 10 cm, keep moving forward
  drive.goForward(SPEED);
  for (;;) {
    if (
      sensorFrontCenter.isImmediatelyBlocked() ||
      (sensorFrontRight.isImmediatelyBlocked() && !sensorRight.isImmediatelyBlocked()) ||
      (sensorFrontLeft.isImmediatelyBlocked() && !sensorLeft.isImmediatelyBlocked())
    ) break;
      /*
      //THERE IS A WALL VERY CLOSE
      if (sensorLeft.isImmediatelyBlocked()) {
        //TURN RIGHT AWAY FROM THE WALL
        makeRightTurn();
      } else if (sensorRight.isImmediatelyBlocked()) {
        //TURN LEFT AWAY FROM THE WALL
        makeLeftTurn();
      }
      */
  }
  drive.halt();
}

void makeLeftTurn() {
  int desiredYaw = (getYaw() + 90); 
  drive.turnLeft(SPEED);
  /*while (((int)getYaw() % 360) < (desiredYaw - 1)) { //the + 2 is to give some room for error
    continue;
  }*/
  delay(1500);
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
  drive.turnRight(SPEED);
  /*while (((int)getYaw() % 360) > (desiredYaw + 1)) { //the + 2 is to give some room for error
    continue;
  }*/
  delay(1500);
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
    drive.goForward(SPEED);
    delay(1800);
    drive.halt();
    makeLeftTurn();

  } else if (sensorLeft.isClear()) {

    int t = millis();
    makeLeftTurn();
    drive.goForward(SPEED);
    delay(1800);
    drive.halt();
    makeRightTurn(); 
  }

}

void loop() {
  
  //while we're in the obstacle area, keep traveling forward and avoiding obstacles
  
  while (sensorLeft.distToNearestObj() <= (STRAIGHTAWAYWIDTH - ROVERWIDTH) && sensorRight.distToNearestObj() <= (STRAIGHTAWAYWIDTH - ROVERWIDTH)) {
    moveForwardUntilBlocked();
    maneuverAround();
  }
  /*
  drive.goForward(SPEED);
  int dist = 0;

  while (!sensorFrontCenter.isImmediatelyBlocked()) {
    dist = sensorLeft.distToNearestObj() + sensorRight.distToNearestObj() + ROVERWIDTH;
    if (dist < (SEARCHWIDTH - 5)) {
      drive.halt();
      break;      
    }
  }
  makeLeftTurn();
  drive.goBackward(SPEED);
  while (!sensorBack.isImmediatelyBlocked()){
    continue;
  }
  drive.halt();

  m.set_rotation(Mechanism::CLAW, 0);
  m.set_rotation(Mechanism::TILT, 110);
  exit(0);
  */
  

  /*
  //we are now in the search area
  //first, we need to make sure the rover is pointing straight ahead. Turn right until we are within -2 to +2 yaw
  drive.turnRight(SPEED);
  while ((((int)getYaw() % 360) < (originalYaw - 2)) || (((int)getYaw() % 360) < (originalYaw + 2))) {
    continue;
  }
  drive.halt();
  
  //make sure we're in the search area
  drive.goForward(SPEED);
  while ((sensorFrontCenter.distToNearestObj() > 80) || ((sensorLeft.distToNearestObj() + sensorRight.distToNearestObj() + ROVERWIDTH) < 90)) {
    continue;
  }
  drive.halt();


  //OKAY, SO for the search part of the algorithm, I have pseudocode but haven't finished writing the actual code yet

  if ((sensorFrontCenter.distToNearestObj() < 80)) {
    //the object must be in view of the front sensor, so try to go over and pick it up
  } else if ((sensorLeft.distToNearestObj() + sensorRight.distToNearestObj() + ROVERWIDTH) < 90) {
    //the object must be in view of one of the side sensors. determine which one by moving forward and comparing distances, then go try to pick it up
  }
  */

}