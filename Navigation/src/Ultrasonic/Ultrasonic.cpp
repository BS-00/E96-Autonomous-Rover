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
  if (read() && (distCm() >= (ROVERLENGTH + 5))){
    return true;
  }
   return false;
}

bool UltSonSr::isBlocked () {
  if (read() && (distCm() <= 15)){
    return true;
  }
   return false;
}

long UltSonSr::distCm () {
  if (read()) {
    return _lastDistCm;
  }
  return DISTANCEOUTOFRANGE;
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
  return microsecs / SPEEDOFSOUNDMICROSECPERCM;
}



