#ifndef Drivetrain_h
#define Drivetrain_h

class Drivetrain{
  public:
    void init();
    void goForward(int speed);
    void goBackward(int speed);
    void turnLeft(int speed);
    void turnRight(int speed);
    void halt();

  private:
    // Individual Motor Control
	
    void setFrontLeft(int speed, bool direction);
    void stopFrontLeft();
    void setFrontRight(int speed, bool direction);
    void stopFrontRight();

    void setBackLeft(int speed, bool direction);
    void stopBackLeft();
    void setBackRight(int speed, bool direction);
    void stopBackRight();
};

#endif
