#include <Arduino.h>
#include "Rover.hpp"
#include "src/ClawAssembly/ClawAssembly.hpp"
#include "src/Ultrasonic/Ultrasonic.hpp"
#include "src/Drivetrain/Drivetrain.hpp"
#include "src/MPU/MPU.hpp"
#include "src/Constants.hpp"

#include <Arduino.h>

bool Rover::init () {
  sensorFCenter.init(47, 46);
  sensorFL.init(23, 22);
  sensorFR.init(49, 48);
  sensorL.init(43, 42);
  sensorR.init(51, 50);
  sensorBack.init(45, 44);

  drive.init();
  gyro.init();
  assem.init(110, 90);
}

void Rover::grabObj () {
  assem.set_rotation(ClawAssembly::CLAW, CLAWASSEM_CLAW_CLOSE_DEG);
  delay(GRAB_TILT_DELAY_MILLIS);
  assem.set_rotation(ClawAssembly::TILT, 90-CLAWASSEM_TILT_DEG);
}

bool Rover::isInObjZone() {
  const int MAX_STRAIGNT_READ_WIDTH = WIDTH_STRAIGHTAWAY_CM - ROVER_WIDTH_CM;
  if ((sensorL.distCm() > MAX_STRAIGNT_READ_WIDTH && sensorL.distCm() < OBJZONE_WIDTH_CM)
  || (sensorR.distCm() > MAX_STRAIGNT_READ_WIDTH && sensorR.distCm() < OBJZONE_WIDTH_CM)) return true;
  return false;
}