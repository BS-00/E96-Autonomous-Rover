#include "Mechanism.hpp"
#include <Arduino.h>

Mechanism::Mechanism (const int claw_pin, const int tilt_pin) {
  _claw_pin = claw_pin;
  _tilt_pin = tilt_pin;
}

void Mechanism::init (const int claw_start_deg, const int mechanism_start_tilt_deg) {
  _claw_servo = Servo();
  _claw_servo.attach(_claw_pin);
  _claw_servo.write(claw_start_deg);

  _tilt_servo = Servo();
  _tilt_servo.attach(_tilt_pin);
  _tilt_servo.write(mechanism_start_tilt_deg);
}

bool Mechanism::set_rotation(ServoType s, int deg) const {
  if (deg < 0 || deg > 180) return false;
  ((s == CLAW) ? _claw_servo : _tilt_servo).write(deg);
  return true;
}

int Mechanism::read_servo_deg(ServoType s) const {
  return ((s == CLAW) ? _claw_servo : _tilt_servo).read();
}