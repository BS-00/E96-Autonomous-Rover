#include <Arduino.h>
#include "Ultrasonic.hpp"
#include "../Constants.hpp"

bool UltSonSr::init (int trigPin, int echoPin) {
  _trigPin = trigPin;
  _echoPin = echoPin;

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  return true;
}

bool UltSonSr::hasSpace () {
  if (read() && (distCm() >= (ROVER_WIDTH_CM + 5))){
    return true;
  }
   return false;
}

bool UltSonSr::isBlocked () {
  if (read() && (distCm() <= ULTSON_ISBLOCKED_THRESHOLD_CM)){
    return true;
  }
   return false;
}

long UltSonSr::distCm () {
  if (read() && _lastDistCm < ULTSON_MAX_DIST_CM && _lastDistCm > ULTSON_MIN_DIST_CM) {
    return _lastDistCm;
  }
  return ULTSON_OUT_OF_RANGE;
}

bool UltSonSr::read () {
  digitalWrite(_trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(_trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(_trigPin, LOW);

  long tMicrosec = pulseIn(_echoPin, HIGH);
  _lastDistCm = max(microSecToCm(tMicrosec) / 2, -1);
  
  if (_lastDistCm < 0) return false;
  return true;
}

long UltSonSr::microSecToCm (int microsecs) {
  const float SPEED_SOUND_MICROSEC_PER_CM = 29.1;
  return microsecs / SPEED_SOUND_MICROSEC_PER_CM;
}



