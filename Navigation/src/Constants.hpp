#ifndef Constants_h
#define Constants_h

#include "Pins.hpp"

//Course Dims
#define LEN_STRAIGHTAWAY_CM 383
#define WIDTH_STRAIGHTAWAY_CM 110
#define ROVER_LEN_CM 32
#define ROVER_WIDTH_CM 23
#define OBJZONE_WIDTH_CM 228
#define OBJZONE_LEN_CM 0 //???

//Motors
#define MOTOR_MAX_SPEED 255
#define MOTOR_MIN_SPEED 100

#define DRIFT_TOWARD_LEFT true
#define DRIFT_COMPENSATION 15
#define MOTOR_DEFAULT_SPEED 210

#define SPEED_CALCULATION_DELAY_MILLIS 50

//Claw assembly
#define CLAWASSEM_CLAW_CLOSE_DEG 7
#define CLAWASSEM_TILT_DEG 10
#define GRAB_TILT_DELAY_MILLIS 500

//Ultrasonic sensor
#define ULTSON_MAX_DIST_CM 375
#define ULTSON_MIN_DIST_CM 2

#define ULTSON_OUT_OF_RANGE ULTSON_MAX_DIST_CM
#define ULTSON_ISBLOCKED_THRESHOLD_CM 7

//MPU
//I2C address of the MPUADDRESS (b1101000/b1101001 for AC0 low/high datasheet sec. 9.2)
#define MPUADDRESS 0x68
//Register 6B - Power Management (Sec. 4.28)
#define MPU6B 0x6B
//SLEEP register to 0. (Required; see Note on p. 9)
#define MPUSLEEP 0x00
//Register 1B - Gyroscope Configuration (Sec. 4.4) 
#define MPU1B 0x1B
#define MPU47 0x47


#endif
