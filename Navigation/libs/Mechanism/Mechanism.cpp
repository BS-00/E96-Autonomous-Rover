#include "mechanism.hpp"

Mechanism::Mechanism (const int claw_pin, const int tilt_pin) {
  _claw_pin = claw_pin;
  _tilt_pin = tilt_pin;
}

void Mechanism::init (float CLAW_START_DEG, float MECHANISM_START_TILT_DEG) {
  _claw_servo = Servo();
  _claw_servo.attach(_claw_pin);
  _claw_servo.write(CLAW_START_DEG);

  _tilt_servo = Servo();
  _tilt_servo.attach(_tilt_pin);
  _tilt_servo.write(MECHANISM_START_TILT_DEG);
}

bool Mechanism::set_rotation(ServoType s, float deg) const {
  if (deg > 0 || deg < 180) return false;
  ((s == CLAW) ? _claw_servo : _tilt_servo).write(deg);
  return true;
}

float Mechanism::read_servo_deg(ServoType s) const {
  return ((s == CLAW) ? _claw_servo : _tilt_servo).read();
}