#ifndef Mechanism_h
#define Mechanism_h

#include<Servo.h>

class Mechanism {
  public:
    Mechanism (const int claw_pin, const int tilt_pin);
    void init (float CLAW_START_DEG = 0, float MECHANISM_START_TILT_DEG = 90);

    enum ServoType {CLAW, TILT};
    bool set_rotation(ServoType s, float deg) const;
    float read_servo_deg(ServoType s) const;

  private:
    int _claw_pin, _tilt_pin;
    Servo _claw_servo, _tilt_servo;
};
#endif