#ifndef Constants_h
#define Constants_h

#include "Pins.hpp"

//Course Dims
#define STRAIGHTAWAYLEN 383 //383 cm, or 13 feet
#define STRAIGHTAWAYWIDTH 110 //110 cm, or 45 inches
#define ROVERLENGTH 32 //cm
#define ROVERWIDTH 23 //cm
#define SEARCHWIDTH 228

//Rover Specifications
#define SPEED 200 //0-255
#define TURNDELAY 1450 //millis
#define AVOIDDELAY 1750 //millis
#define TILTAMOUNT 15 //degrees
#define GRABDELAY 600 //millis
#define OBJZONEDELAY 200
#define TURNCORRECTIONDELAY 500

#define DRIFTCOMPENSATION 15

//Ultrasonic sensor
#define DISTANCEOUTOFRANGE 10000
#define SPEEDOFSOUNDMICROSECPERCM 29.1

//MPU
//This is the I2C address of the MPUADDRESS (b1101000/b1101001 for AC0 low/high datasheet sec. 9.2)
#define MPUADDRESS 0x68
//Accessing the register 6B - Power Management (Sec. 4.28)
#define MPU6B 0x6B
//Setting SLEEP register to 0. (Required; see Note on p. 9)
#define MPUSLEEP 0x00
//Accessing the register 1B - Gyroscope Configuration (Sec. 4.4) 
#define MPU1B 0x1B
#define MPU47 0x47


#endif
