
#include "gyroscope.h"
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  gyroSetup();
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print("Yaw: "); Serial.println(getYaw());
  delay(50);
}
