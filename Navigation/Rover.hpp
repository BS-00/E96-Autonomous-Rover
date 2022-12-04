#ifndef Rover_h
#define Rover_h

#include "src/ClawAssembly/ClawAssembly.hpp"
#include "src/Ultrasonic/Ultrasonic.hpp"
#include "src/Drivetrain/Drivetrain.hpp"
#include "src/MPU/MPU.hpp"

struct Rover {
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
  void grabObj ();
  bool isInObjZone();
};


#endif