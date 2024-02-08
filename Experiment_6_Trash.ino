#include <Servo.h>
#include <Stepper.h>

const int SERVO_PIN = 6;
const int trigPin = 3;
const int echoPin = 4;
const int DISTANCE_THRESHOLD = 5;
const int DISTANCE_COMPACT = 50000;
const int stepsPerRevolution = 2038;

Servo myservo;
Stepper myStepper = Stepper(stepsPerRevolution, 8, 10, 9, 11);


float duration_us, distance_cm;

void setup() {
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT); 
  Serial.begin(9600); 

  myservo.attach(SERVO_PIN);
  myservo.write(90);
}
void loop() {

  sonar_Sense();
  if(distance_cm < DISTANCE_THRESHOLD){
    for (int x =0; x < 4; x++) {
      stepper_Backward();
    }
    delay(500);
    myservo.write(0); 
    delay(1000);
    myservo.write(90);
    delay(500); 
    myservo.write(0); 
    delay(1000);
    myservo.write(90); 
    delay(500);
    myservo.write(0); 
    delay(1000);
    myservo.write(90); 
    delay(500);
    for (int x =0; x < 4; x++) {
      stepper_Forward();
    }
    delay(500);
  }
  
  // print the value to Serial Monitor
  Serial.print("distance: ");
  Serial.print(distance_cm);
  Serial.println(" cm");

  delay(500);  
}
void sonar_Sense() {
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration_us = pulseIn(echoPin, HIGH);
  distance_cm = 0.017 * duration_us;
}

void stepper_Forward() {
  myStepper.setSpeed(15);
	myStepper.step(stepsPerRevolution);
  delay(2000);
}

void stepper_Backward() {
  myStepper.setSpeed(15);
	myStepper.step(-stepsPerRevolution);
  delay(2000);
}