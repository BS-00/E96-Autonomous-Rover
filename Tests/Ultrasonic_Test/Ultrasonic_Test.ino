#include "ultrasonic.h"

#define N_SENSORS 6
UltSonSr sensors[N_SENSORS];
const int SENSOR_PINS[][2] = {{51, 50}, {49, 48}, {47, 46}, {45, 44}, {43, 42}, {23, 22}};

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  for (int i = 0; i < N_SENSORS; i++){
    sensors[i] = UltSonSr(SENSOR_PINS[i][0], SENSOR_PINS[i][1]);
  }
}

void loop() {
  for (int i = 0; i < N_SENSORS; i++) sensors[i].read();
  
  Serial.println("Front Left: " + String(sensors[5].distToNearestObj()));
  Serial.println("Front Middle: " + String(sensors[2].distToNearestObj()));
  Serial.println("Front Right: " + String(sensors[1].distToNearestObj()));
  Serial.println("Right: " + String(sensors[0].distToNearestObj()));
  Serial.println("Back: " + String(sensors[3].distToNearestObj()));
  Serial.println("Left: " + String(sensors[4].distToNearestObj()));
  Serial.println("------------------------------");
  delay(500);
}
