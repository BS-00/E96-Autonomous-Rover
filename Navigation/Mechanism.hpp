#ifndef Mechanism_h
#define Mechanism_h

#include<Servo.h>

class Mechanism {
  public:
    Mechanism (const int claw_pin, const int tilt_pin);
    void init (const int claw_start_deg, const int mechanism_start_tilt_deg);

    enum ServoType {CLAW, TILT};
    bool set_rotation(ServoType s, int deg) const;
    int read_servo_deg(ServoType s) const;

  private:
    int _claw_pin, _tilt_pin;
    Servo _claw_servo, _tilt_servo;
};
#endif