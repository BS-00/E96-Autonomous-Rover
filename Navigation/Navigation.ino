#include "src/Constants.hpp"
#include "Rover.hpp"

#include <Wire.h>

Rover bruver;

void setup() {
  Serial.begin(9600);
  Wire.begin();

  bruver.init();
}

void loop() {
  

  /*
  //while we're in the obstacle area, keep traveling forward and avoiding obstacles
  const int BUFFER = 5;
  while (!bruver.isInObjZone()) {
    bruver.forwardUntilBlocked();
    if (bruver.isInObjZone()) break;
    bruver.avoidObstacle();
  }

  */
  bruver.drive.goForward(SPEED);
  int dist = 0;

  while (!bruver.sensorFCenter.isBlocked()) {
    dist = bruver.sensorL.distCm() + bruver.sensorR.distCm() + ROVERWIDTH;
    if (dist < (SEARCHWIDTH - 5)) {
      bruver.drive.halt();
      break;      
    }
  }
  bruver.turn(Rover::LEFT);
  bruver.drive.goBackward(SPEED);
  for (;;) if (bruver.sensorBack.isBlocked()) break;
  bruver.drive.halt();

  bruver.grab();
  exit(0);
  
  
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
