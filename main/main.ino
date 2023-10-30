#include <Servo.h>

// undefine stdlib's abs if encountered
#ifdef abs
#undef abs
#endif
#define abs(x) ((x)>0?(x):-(x))


// Define Servo 
const byte servoPin = 11;
Servo servo;
const byte servoMin=46;
const byte servoMax=135;

int currentSteering;

// Define variables
const byte motorPin = 6;
const byte minSpeed=100;
const byte maxSpeed = 150;

const byte directionPin1 = 4;
const byte directionPin2 = 5;

int currentSpeed;

void setup() {
  // Servo setup
  pinMode(servoPin, OUTPUT);
  servo.attach(servoPin);
  currentSteering = 0;
  setSteering(currentSteering); // Move wheels to straight forwards

  // Motor setup
  pinMode(motorPin, OUTPUT);
  currentSpeed=0;
  setSpeed(currentSpeed);

  pinMode(directionPin1, OUTPUT);
  pinMode(directionPin2, OUTPUT);


  // Start serial communication
  Serial.begin(9600);
}

void loop() {
  // Speed up motor then slow down again

  for (currentSpeed = 0; currentSpeed < 100; currentSpeed++) {
    setSpeed(currentSpeed);
    delay(100);
  }
  for (currentSpeed = 100; currentSpeed > 0; currentSpeed--) {
    setSpeed(currentSpeed);
    delay(100);
  }


  for (currentSpeed = 0; currentSpeed >-100; currentSpeed--) {
    setSpeed(currentSpeed);
    delay(100);
  }
  for (currentSpeed = -100; currentSpeed < 0; currentSpeed++) {
    setSpeed(currentSpeed);
    delay(100);
  }

}

void setSpeed(int speed) {
  /* Params: speed: int between -100 and 100 where -100 is maximum backwards 
    and 100 is maximum forwards 
  */ 
  // Cancel the action if trying to steer more than allowed
  if (abs(speed) > 100) {
    return;
  }

  // Set direction
  if (speed > 0) {
    digitalWrite(directionPin2, LOW);
    digitalWrite(directionPin1, HIGH);
  } else if (speed < 0) {
    digitalWrite(directionPin1, LOW);
    digitalWrite(directionPin2, HIGH);
  } else {
    digitalWrite(directionPin1, LOW);
    digitalWrite(directionPin2, LOW);
  }

  // Map the value into servo degrees
  const int motorPower = map(abs(speed), 0, 100, minSpeed, maxSpeed);
  analogWrite(motorPin, motorPower);
  return;
}


void setSteering(int steering) {
  /* Params: steering: int between -100 and 100 where -100 is maximum turning to left 
    and 100 is maximum to right¨  
  */ 
  // Cancel the action if trying to steer more than allowed
  if (abs(steering) > 100) {
    return;
  }
  // Map the value into servo degrees
  const int servoAngle = map(steering, 100, -100, servoMin, servoMax);
  servo.write(servoAngle);
  return;
}
