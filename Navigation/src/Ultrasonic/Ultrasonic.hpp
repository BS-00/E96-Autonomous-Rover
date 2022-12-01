#ifndef Ultrasonic_h
#define Ultrasonic_h

class UltSonSr {
  public:
    bool init (int trigPin, int echoPin);
    bool hasSpace ();
    bool isBLocked ();
    long lastDistCm ();
  
  private:
    int _trigPin, _echoPin;
    long _lastDistCm;

    bool read ();
    long microSecToCm (int microsecs) const;
};

#endif
