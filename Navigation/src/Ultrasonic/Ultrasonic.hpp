#ifndef Ultrasonic_h
#define Ultrasonic_h

class UltSonSr {
  public:
    bool init (int trigPin, int echoPin);
    bool hasSpace ();
    bool isBlocked ();
    long distCm ();
  
  private:
    int _trigPin, _echoPin;
    long _lastDistCm = NULL;

    bool read ();
    long microSecToCm (int microsecs);
};

#endif
