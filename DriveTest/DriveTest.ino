#include "Drivetrain.h"

Drivetrain drivetrain;

void setup() {
  // put your setup code here, to run once:
  drivetrain.init();

  drivetrain.goForward(124);
  delay(2000);
  drivetrain.goBackward(200);
  delay(2000);
  drivetrain.turnLeft(200);
  delay(2000);
  drivetrain.turnRight(200);
  delay(2000);
  drivetrain.halt();
}

void loop() {
  // put your main code here, to run repeatedly:
}
