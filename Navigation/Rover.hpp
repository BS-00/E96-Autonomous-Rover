#ifndef Rover_h
#define Rover_h

#include "src/ClawAssembly/ClawAssembly.hpp"
#include "src/Ultrasonic/Ultrasonic.hpp"
#include "src/Drivetrain/Drivetrain.hpp"
#include "src/MPU/MPU.hpp"

class Rover {
  
  public:
    enum Direction {FORWARD, BACKWARD, LEFT, RIGHT};
    Direction orientation = FORWARD;
    
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

  void forwardUntilBlocked ();
  void avoidObstacle ();
  void turn (Direction dir);
  void grab ();
  bool isInObjZone();

  private:
    float _originalYaw = 0.0;
};


#endif