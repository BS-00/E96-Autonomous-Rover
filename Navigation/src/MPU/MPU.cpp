#include <Arduino.h>
#include <Wire.h>
#include "MPU.hpp"
#include "../Constants.hpp"

bool MPU::init () {
  Wire.beginTransmission(MPUADDRESS); 
  Wire.write(MPU6B); 
  Wire.write(MPUSLEEP);
  Wire.endTransmission();  
  Wire.beginTransmission(MPUADDRESS);
  Wire.write(MPU1B); 
  Wire.write(0x00000000); //Setting the gyro to full scale +/- 250deg./s 
  Wire.endTransmission(); 

  _gyroErrorZ = error();
  _currentTime = millis();
  
  return true;
}

float MPU::yaw () {

  _previousTime = _currentTime;
  _currentTime = millis();
  _elapsedTime = (_currentTime - _previousTime)/1000; //conversion to s

  //read only the yaw bytes from the gyroscope
  Wire.beginTransmission(MPUADDRESS);
  Wire.write(MPU47);
  Wire.endTransmission();
  Wire.requestFrom(MPUADDRESS, 2);
  while (Wire.available() < 2);
  _gyroZ = (Wire.read() << 8 | Wire.read());
  
  //error correction:
  _gyroZ = _gyroZ  / 131.0;
  _gyroZ -= _gyroErrorZ;
  _yaw = _yaw + _gyroZ * _elapsedTime;

  return _yaw;
}

float MPU::error () {

  float zCur = 0;
  float zTot = 0;
  float zErr = 0;

  for(int i = 0; i < 200; ++i){
	Wire.beginTransmission(MPUADDRESS);
	Wire.write(MPU47);
	Wire.endTransmission();
	Wire.requestFrom(MPUADDRESS, 2);
	while (Wire.available() < 2);
	zCur = (Wire.read() << 8 | Wire.read());

	zTot = zTot + (zCur / 131.0);
  }
  zErr = zTot / 200;
  return zErr;
}