#include "Mechanism.hpp"

const int CLAW_PIN = 2, TILT_PIN = 3;
Mechanism m = Mechanism(CLAW_PIN, TILT_PIN);

const int CLAW_START_DEG = 80, MECHANISM_START_DEG = 90;

void setup() {
  m.init(CLAW_START_DEG, MECHANISM_START_DEG);
  delay(3000);
  m.set_rotation(Mechanism::CLAW, 0);
  delay(3000);
  m.set_rotation(Mechanism::TILT, 120);
  delay(3000);
  m.set_rotation(Mechanism::TILT, 60);
  delay(3000);
  m.set_rotation(Mechanism::TILT, MECHANISM_START_DEG);
  delay(3000);
  m.set_rotation(Mechanism::CLAW, CLAW_START_DEG);
  
  Serial.begin(9600);
  Serial.println("Current claw position: " + String(m.read_servo_deg(Mechanism::CLAW)) + " degrees");
  Serial.println("Current tilt position: " + String(m.read_servo_deg(Mechanism::TILT)) + " degrees");
}

void loop() {

}
