#ifndef Rover_h
#define Rover_h

#include "src/ClawAssembly/ClawAssembly.hpp"
#include "src/Ultrasonic/Ultrasonic.hpp"
#include "src/Drivetrain/Drivetrain.hpp"
#include "src/MPU/MPU.hpp"

enum Direction {FORWARD, BACKWARD, LEFT, RIGHT};

class Rover {
  public:
    UltSonSr  sensorFCenter,
          sensorFL,
          sensorFR,
          sensorL,
          sensorR,
          sensorBack;
    Drivetrain drive;
    ClawAssembly assem;
    MPU gyro;
	
  bool init ();
  void turn (Direction dir);
  void grabObj ();
  bool isInObjZone();
};


#endif