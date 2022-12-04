#include "src/Constants.hpp"
#include "Rover.hpp"

#include <Wire.h>

Rover bruver;
float startYaw;

void setup() {
  Serial.begin(9600);
  Wire.begin();

  bruver.init();
  startYaw = bruver.gyro.yaw();
}

void loop() {
  const double FLRScale = .5, LRScale = .25, FCScale = .25;
  if (FLRScale + LRScale + FCScale != 1) exit(0);

  const double minPossibleDist = 3 * ULTSON_MIN_DIST_CM;
  const double maxPossibleDist = 3 * ULTSON_MAX_DIST_CM;

  //# in the obstacle area, keep traveling forward and avoiding obstacles
  while (!bruver.isInObjZone()) {
    double weightedLDist = bruver.sensorFL.distCm()*FLRScale+bruver.sensorL.distCm()*LRScale;
    double weightedRDist = bruver.sensorFR.distCm()*FLRScale+bruver.sensorR.distCm()*LRScale; 
    double weightedFCenterDist = bruver.sensorFCenter.distCm()*FCScale;

    ((weightedLDist > weightedRDist) ? weightedLDist : weightedRDist) += weightedFCenterDist;

    int leftSpeed = floor(map(weightedRDist, minPossibleDist, maxPossibleDist, MOTOR_MIN_SPEED, MOTOR_MAX_SPEED));
    int rightSpeed = floor(map(weightedLDist, minPossibleDist, maxPossibleDist, MOTOR_MIN_SPEED, MOTOR_MAX_SPEED));

    bruver.drive.forward(leftSpeed, rightSpeed);
    delay(SPEED_CALCULATION_DELAY_MILLIS);
  }

  //# entered the object zone and exited the obstacle area
  bruver.drive.halt();
  
  //# move the rover to the center of the objzone
  //THIS COULD MESS UP THE GYRO READING BY 360 IF USING THE GYRO IMPLEMENTATION
  const int OBJZONE_WALL_BUFFER_CM = 15;

  bruver.drive.turnLeft(MOTOR_DEFAULT_SPEED);
  for (;;) if (bruver.sensorL.distCm() + bruver.sensorR.distCm() + ROVER_WIDTH <= OBJZONE_WIDTH_CM + OBJZONE_WALL_BUFFER_CM &&
               bruver.sensorL.distCm() + bruver.sensorR.distCm() + ROVER_WIDTH >= OBJZONE_WIDTH_CM - OBJZONE_WALL_BUFFER_CM
              ) break;
  bruver.drive.halt();

  if (bruver.sensorFCenter.distCm() > bruver.sensorBack.distCm()) bruver.drive.backward(MOTOR_DEFAULT_SPEED, MOTOR_DEFAULT_SPEED);
  else bruver.drive.forward(MOTOR_DEFAULT_SPEED, MOTOR_DEFAULT_SPEED);

  //ADD A BUFFER HERE???
  for (;;) if (bruver.sensorFCenter.distCm() == bruver.sensorBack.distCm()) break;
  bruver.drive.halt();

  //# make the rover face forward
  /*
  //gyroscope implementation:
  const int HALF_TURN_BUFFER_DEG = 1;
  while ((((int)bruver.gyro.yaw() % 360) < (startYaw - HALF_TURN_BUFFER_DEG)) || (((int)bruver.gyro.yaw() % 360) < (startYaw + HALF_TURN_BUFFER_DEG))) {
    //CHECK TO SEE WHEN IT SHOULD TURN RIGHT/LEFT BECAUSE I HAVE NO IDEA
    if (bruver.gyro.yaw() < (startYaw)) bruver.drive.turnRight(MOTOR_DEFAULT_SPEED);
    else bruver.drive.turnRight(MOTOR_DEFAULT_SPEED);
  }
  */
  //*
  //no-gyroscope implementation:
  const int BUFFER_CM = 2;
  bool isTurningRight;
  while (bruver.sensorFCenter.distCm() > OBJZONE_LEN_CM - BUFFER_CM) {
    //rover is not facing forward
    if (isTurningRight) bruver.drive.turnRight(MOTOR_DEFAULT_SPEED);
    else bruver.drive.turnLeft(MOTOR_DEFAULT_SPEED);

    if (bruver.sensorFCenter.distCm() == OBJZONE_WIDTH_CM ||
        bruver.sensorFCenter.distCm() < OBJZONE_LEN_CM) {
      isTurningRight = !isTurningRight;
    }
  }
  //*/

  //# check for the object on either side and infront
  bruver.drive.forward(MOTOR_DEFAULT_SPEED, MOTOR_DEFAULT_SPEED);
  //MIGHT NEED TO ADD A DELAY HERE SO THE SENSOR DOSENT PICK UP PART OF THE WALL NEARBY THE ENTERANCE AND COUNT IT AS AN OBJECT

  const int MAX_WALL_DIST_CM = (OBJZONE_WIDTH_CM-ROVER_WIDTH_CM)/2;

  bool objectIsRight;
  for (;;) {
    if (bruver.sensorL.distCm() < MAX_WALL_DIST_CM - OBJZONE_WALL_BUFFER_CM) break;
    else if (bruver.sensorR.distCm() < MAX_WALL_DIST_CM - OBJZONE_WALL_BUFFER_CM) {
      objectIsRight = true;
      break;
    } 
    else if (bruver.sensorFCenter.distCm() <= ULTSON_ISBLOCKED_THRESHOLD_CM) exit(0);
  }
  bruver.drive.halt();

  //# once object is located, turn claw to face and backup toward object
  if (objectIsRight) bruver.drive.turnLeft(MOTOR_DEFAULT_SPEED);
  else bruver.drive.turnRight(MOTOR_DEFAULT_SPEED);

  //turn until the back sensor finds the object
  for (;;) if (bruver.sensorBack.distCm() < MAX_WALL_DIST_CM - OBJZONE_WALL_BUFFER_CM) break;
  bruver.drive.halt();

  //go backward until the object is reached
  bruver.drive.backward(MOTOR_DEFAULT_SPEED, MOTOR_DEFAULT_SPEED);
  for (;;) if (bruver.sensorBack.distCm() <= ULTSON_ISBLOCKED_THRESHOLD_CM) break;
  bruver.drive.halt();

  bruver.grabObj();

  //# drop at drop zone
  bruver.drive.forward(MOTOR_DEFAULT_SPEED, MOTOR_DEFAULT_SPEED);
  for(;;) if (bruver.sensorFCenter <= ULTSON_ISBLOCKED_THRESHOLD_CM) break;
  bruver.drive.halt();

  exit(0);
}
