#include <Arduino.h>
#include "Ultrasonic.hpp"
#include "../Constants.hpp"

bool UltSonSr::init (int trigPin, int echoPin) {
  _trigPin = trigPin;
  _echoPin = echoPin;

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  read();
  return true;
}

bool UltSonSr::hasSpace () {
  if (read() && (lastDistCm() >= (ROVERLENGTH + 5))){
    return true;
  }
   return false;
}

bool UltSonSr::isBLocked () {
  if (read() && (lastDistCm() <= 15)){
    return true;
  }
   return false;
}

long UltSonSr::lastDistCm () {
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

  if (lastDistCm() < 0) return false;
  return true;
}

long UltSonSr::microSecToCm (int microsecs) const {
  return microsecs / SPEEDOFSOUNDMICROSECPERCM;
}



