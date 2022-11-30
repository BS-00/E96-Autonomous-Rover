#ifndef Ultrasonic_h
#define Ultrasonic_h

#define DISTANCEOUTOFRANGE 10000
#define ROVERLENGTH 32

class UltSonSr {
  public:
    UltSonSr () {}
    UltSonSr (int trigPin, int echoPin) {
      _trigPin = trigPin;
      _echoPin = echoPin;

      pinMode(trigPin, OUTPUT);
      pinMode(echoPin, INPUT);
    }

    bool read () {
      digitalWrite(_trigPin, LOW);
      delayMicroseconds(2);
      digitalWrite(_trigPin, HIGH);
      delayMicroseconds(10);
      digitalWrite(_trigPin, LOW);

      long tMicrosec = pulseIn(_echoPin, HIGH);
      lastDistCm = max(microSecToCm(tMicrosec) / 2, -1);

      if (lastDistCm < 0) return false;
      return true;
    }

    bool isClear() {
      if (read() & (lastDistCm >= (ROVERLENGTH + 5))){
        return true;
      }
      return false;
    }

    bool isImmediatelyBlocked() {
      if (read() & (lastDistCm <= 10)){
        return true;
      }
      return false;
    }

    long distToNearestObj() {
      if (read()) {
        return lastDistCm;
      }
      return DISTANCEOUTOFRANGE;
    }
  
  private:
    int _trigPin, _echoPin;
    long lastDistCm = NULL;

    long microSecToCm (int microsecs) {
      const int SPEED_OF_SOUND_MICROSEC_PER_CM = 29.1;
      return microsecs / SPEED_OF_SOUND_MICROSEC_PER_CM;
    }
};



#endif
