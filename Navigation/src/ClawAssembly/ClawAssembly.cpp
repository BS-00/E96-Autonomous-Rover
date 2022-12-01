#include <Arduino.h>
#include "ClawAssembly.hpp"
#include "../Constants.hpp"

#include <Arduino.h>

void ClawAssembly::init(const int claw_start_deg, const int start_tilt_deg) {
  _claw_servo = Servo();
  _claw_servo.attach(CLAWPIN);
  _claw_servo.write(claw_start_deg);

  _tilt_servo = Servo();
  _tilt_servo.attach(TILTPIN);
  _tilt_servo.write(start_tilt_deg);
}

bool ClawAssembly::set_rotation(ServoType s, int deg) const {
  if (deg < 0 || deg > 180) return false;
  ((s == CLAW) ? _claw_servo : _tilt_servo).write(deg);
  return true;
}

int ClawAssembly::read_servo_deg(ServoType s) const {
  return ((s == CLAW) ? _claw_servo : _tilt_servo).read();
}