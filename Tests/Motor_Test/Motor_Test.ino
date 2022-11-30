const int FRONT_EN_A = 5, FRONT_EN_B = 6;
const int FRONT_A_IN1 = 31, FRONT_A_IN2 = 30, FRONT_B_IN1 = 28, FRONT_B_IN2 = 29;

const int BACK_EN_A = 10, BACK_EN_B = 9;
const int BACK_A_IN1 = 37, BACK_A_IN2 = 36, BACK_B_IN1 = 34, BACK_B_IN2 = 35;

const int MOTOR_SPEED = 150;

void setup() {
  // put your setup code here, to run once:
  pinMode(FRONT_EN_A, OUTPUT);
  pinMode(FRONT_EN_B, OUTPUT);

  pinMode(FRONT_A_IN1, OUTPUT);
  pinMode(FRONT_A_IN2, OUTPUT);
  
  pinMode(FRONT_B_IN1, OUTPUT);
  pinMode(FRONT_B_IN2, OUTPUT);

  //BACK
  pinMode(BACK_EN_A, OUTPUT);
  pinMode(BACK_EN_B, OUTPUT);

  pinMode(BACK_A_IN1, OUTPUT);
  pinMode(BACK_A_IN2, OUTPUT);
  
  pinMode(BACK_B_IN1, OUTPUT);
  pinMode(BACK_B_IN2, OUTPUT);

  Serial.begin(9600);
}

void loop() {

  Serial.println("Running!");

  // FRONT
  analogWrite(FRONT_EN_A, MOTOR_SPEED);
  digitalWrite(FRONT_A_IN1, HIGH);
  digitalWrite(FRONT_A_IN2, LOW);

  analogWrite(FRONT_EN_B, MOTOR_SPEED);
  digitalWrite(FRONT_B_IN1, HIGH);
  digitalWrite(FRONT_B_IN2, LOW);


  // BACK
  analogWrite(BACK_EN_A, MOTOR_SPEED);
  digitalWrite(BACK_A_IN1, HIGH);
  digitalWrite(BACK_A_IN2, LOW);

  analogWrite(BACK_EN_B, MOTOR_SPEED);
  digitalWrite(BACK_B_IN1, HIGH);
  digitalWrite(BACK_B_IN2, LOW);
}
