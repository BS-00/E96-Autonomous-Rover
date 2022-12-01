#ifndef MPU_h
#define MPU_h

class MPU {
	public:
	  bool init ();
	  float yaw ();
		
	private:
	  float _yaw = 0;
	  float _gyroZ, _gyroErrorZ;
	  float _elapsedTime, _currentTime, _previousTime;
		
	  float error();
};


#endif