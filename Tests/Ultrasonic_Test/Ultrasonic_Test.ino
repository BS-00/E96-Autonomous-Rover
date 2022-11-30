#include "ultrasonic.h"

#define N_SENSORS 6
const int SENSOR_PINS[][2] = {{51, 50}, {49, 48}, {47, 46}, {45, 44}, {43, 42}, {23, 22}};
UltSonSr* sensors;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  for (int i = 0; i < N_SENSORS; i++){
    sensors[i] = UltSonSr(SENSOR_PINS[i][0], SENSOR_PINS[i][1]);
  }
}

const int WAIT_TIME_MILLIS = 100;
void loop() {
  for (int i = 0; i < N_SENSORS; i++) sensors[i].read();

  Serial.println("Front Left: " + String(sensors[5].lastDistCm));
  Serial.println("Front Middle: " + String(sensors[2].lastDistCm));
  Serial.println("Front Right: " + String(sensors[1].lastDistCm));
  Serial.println("Right: " + String(sensors[0].lastDistCm));
  Serial.println("Back: " + String(sensors[3].lastDistCm));
  Serial.println("Left: " + String(sensors[4].lastDistCm));
  delay(WAIT_TIME_MILLIS);
}
