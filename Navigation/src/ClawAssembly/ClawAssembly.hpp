#ifndef ClawAssembly_h
#define ClawAssembly_h

#include <Servo.h>

class ClawAssembly {
  public:
    void init (const int claw_start_deg, const int start_tilt_deg);

    enum ServoType {CLAW, TILT};
    bool set_rotation (ServoType s, int deg) const;
    int read_servo_deg (ServoType s) const;

  private:
    Servo _claw_servo, _tilt_servo;
};

#endif