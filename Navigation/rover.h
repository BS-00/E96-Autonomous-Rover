#ifndef Rover_h
#define Rover_h

#include "Drivetrain.h"
#include "constants.h"

class Rover {
  
  public:
    Rover();

    /*
    void moveForward();
    void updatePosition();
    void makeLeftTurn();
    void makeRightTurn();
    float* getPosition();
    bool isInSearchArea();
    bool isBlocked();*/
    int orientation;
    float m_myLength;
    float m_myWidth;

  private:
    
    
    
    






};

Rover::Rover() {
  m_myLength = 32;
  m_myWidth = 24;
  
  orientation = 0;
}






#endif