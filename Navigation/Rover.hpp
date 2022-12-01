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
    
    UltSonSr  sensorFCenter(),
          sensorFL(),
          sensorFR(),
          sensorL(),
          sensorR(),
          sensorBack();
    Drivetrain drive();
    ClawAssembly assem();
    MPU gyro();
	
  bool init ();

  void forwardUntilBlocked ();
  void avoidObstacle ();
  void turn (Direction dir);
  void grab ();

  int xPosCm () const;
  int yPosCm () const;

  private:
    float _originalYaw = 0.0;
    int _xPosCm = 0, _yPosCm = 0;

    void _updatePos (int startTime);

};


#endif