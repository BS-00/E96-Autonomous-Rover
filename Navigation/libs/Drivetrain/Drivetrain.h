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

    
    // Front Bridge
    int _frontEnA = 5;
    int _frontIn1 = 31;
    int _frontIn2 = 30;

    int _frontEnB = 6;
    int _frontIn3 = 28;
    int _frontIn4 = 29;


    // Back Bridge
    int _backEnA = 10;
    int _backIn1 = 37;
    int _backIn2 = 36;

    int _backEnB = 9;
    int _backIn3 = 34;
    int _backIn4 = 35;

};

#endif
