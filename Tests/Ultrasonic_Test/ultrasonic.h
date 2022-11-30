class UltSonSr {
  public:
    long lastDistCm = NULL;

    UltSonSr();
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
  
  private:
    int _trigPin, _echoPin;

    long microSecToCm (int microsecs) {
      const int SPEED_OF_SOUND_MICROSEC_PER_CM = 29.1;
      return microsecs / SPEED_OF_SOUND_MICROSEC_PER_CM;
    }
};
