#ifndef Gyroscope_h
#define Gyroscope_h

#include <Wire.h>

const int MPU = 0x68;
float yaw = 0;
float gyroZ, gyroAngleZ, gyroErrorZ;
float elapsedTime, currentTime, previousTime;

float getYaw () {

  previousTime = currentTime;
  currentTime = millis();
  elapsedTime = (currentTime - previousTime)/1000; //conversion to s

  //read only the yaw bytes from the gyroscope
  Wire.beginTransmission(MPU);
  Wire.write(0x47);
  Wire.endTransmission();
  Wire.requestFrom(MPU, 2);
  while (Wire.available() < 2);
  gyroZ = (Wire.read() << 8 | Wire.read());
  
  //error correction:
  gyroZ = gyroZ  / 131.0;
  gyroZ -= gyroErrorZ;
  yaw = yaw + gyroZ * elapsedTime;

  /*
  Serial.print("Current Time: ");
  Serial.print(currentTime / 1000);
  Serial.print(", Yaw: ");
  Serial.print(yaw);
  Serial.print("\n");
  */
  return yaw;
}

float calculateGyroError() {

  float zCur = 0;
  float zTot = 0;
  float zErr = 0;

  for(int i = 0; i < 200; ++i){
    Wire.beginTransmission(MPU);
    Wire.write(0x47);
    Wire.endTransmission();
    Wire.requestFrom(MPU, 2);
    while (Wire.available() < 2);
    zCur = (Wire.read() << 8 | Wire.read());

    zTot = zTot + (zCur / 131.0);
  }
  zErr = zTot / 200;
  return zErr;
}

void gyroSetup() {
  Wire.beginTransmission(MPU); //This is the I2C address of the MPU (b1101000/b1101001 for AC0 low/high datasheet sec. 9.2)
  Wire.write(0x6B); //Accessing the register 6B - Power Management (Sec. 4.28)
  Wire.write(0x00); //Setting SLEEP register to 0. (Required; see Note on p. 9)
  Wire.endTransmission();  
  Wire.beginTransmission(MPU); //I2C address of the MPU
  Wire.write(0x1B); //Accessing the register 1B - Gyroscope Configuration (Sec. 4.4) 
  Wire.write(0x00000000); //Setting the gyro to full scale +/- 250deg./s 
  Wire.endTransmission(); 

  gyroErrorZ = calculateGyroError();
  currentTime = millis();

  Serial.print("\nGyro Error: ");
  Serial.print(gyroErrorZ);
  Serial.print("\n");
}



#endif
