
#include <Robojax_L298N_DC_motor.h>

#define ENA D8 // this pin must be PWM enabled pin if Arduino board is used
#define IN1 D7
#define IN2 D6

const int CCW = 2; // do not change
const int CW  = 1; // do not change

#define motor1 1 // do not change

//Robojax_L298N_DC_motor motor(IN1, IN2, ENA);	
// Watch video instruciton for this line: https://youtu.be/2JTMqURJTwg
Robojax_L298N_DC_motor motor(IN1, IN2, ENA, true);

const int trigPin = D0;
const int echoPin = D1;

//define sound velocity in cm/uS
#define SOUND_VELOCITY 0.034
#define CM_TO_INCH 0.393701

long duration;
float distanceCm;
float distanceInch;

void setup() {
  Serial.begin(115200); // Starts the serial communication
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  motor.begin();
}

void loop() {
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  
  // Calculate the distance
  distanceCm = duration * SOUND_VELOCITY/2;
  
  
  // Prints the distance on the Serial Monitor
  Serial.print("Distance (cm): ");
  Serial.println(distanceCm);

  if(distanceCm>10)
     motor.rotate(motor1, 60, CW);//run motor1 at 60% speed in CW direction
     
    else
      motor.brake(1);
  
  delay(1000);
}

