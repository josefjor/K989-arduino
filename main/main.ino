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
Servo motor; // A ESC for R/C uses the same signals as servos.
const byte maxSpeed = 135; // Set half of motor capacity as max power.

int currentSpeed;

void setup() {
  // Servo setup
  pinMode(servoPin, OUTPUT);
  servo.attach(servoPin);
  currentSteering = 0;
  setSteering(currentSteering); // Move wheels to straight forwards

  // Motor setup
  pinMode(motorPin, OUTPUT);
  motor.attach(motorPin);
  currentSpeed=0;
  setSpeed(currentSpeed);
  

  // Start serial communication
  Serial.begin(9600);
}

void loop() {
  
}

void setSpeed(int speed) {
  /* Params: speed: int between -100 and 100 where -100 is maximum backwards 
    and 100 is maximum forwards¨  
  */ 
  // Cancel the action if trying to steer more than allowed
  if (abs(speed) > 100) {
    return;
  }
  // Map the value into servo degrees
  const int motorPower = map(speed, -100, 100, 180-maxSpeed, maxSpeed);
  motor.write(motorPower);
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
