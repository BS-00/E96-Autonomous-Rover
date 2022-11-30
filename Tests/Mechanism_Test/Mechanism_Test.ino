#include "mechanism.hpp"

const int CLAW_PIN = 0, TILT_PIN = 1;
Mechanism m = Mechanism(CLAW_PIN, TILT_PIN);

const int DELAY_MILLIS = 3000;
void setup() {
  // put your setup code here, to run once:
  m.init();
  m.set_rotation(Mechanism::CLAW, 180);
  delay(DELAY_MILLIS);
  m.set_rotation(Mechanism::CLAW, 0);
  delay(DELAY_MILLIS);
  m.set_rotation(Mechanism::TILT, 180);
  delay(DELAY_MILLIS);
  m.set_rotation(Mechanism::TILT, 80);
  
  Serial.begin(9600);
  Serial.println("Current claw position: " + String(m.read_servo_deg(Mechanism::CLAW)) + " degrees");
  Serial.println("Current tilt position: " + String(m.read_servo_deg(Mechanism::TILT)) + " degrees");
}

void loop() {

}
