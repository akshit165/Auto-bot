#include <Servo.h>          //Servo motor library. This is standard library
#include <NewPing.h>        //Ultrasonic sensor function library. You must install this library
String incomingByte ;  

const int LeftMotorForward = 2;
const int LeftMotorBackward = 3;
const int RightMotorForward = 4;
const int RightMotorBackward = 5;

#define trig_pin A4 //analog input 1
#define echo_pin A5 //analog input 2
#define maximum_distance 200
boolean goesForward = false;
int distance = 100;

NewPing sonar(trig_pin, echo_pin, maximum_distance); //sensor function
Servo servo_motor; //our servo name

void setup(){
  Serial.begin(9600);
  pinMode(RightMotorForward, OUTPUT);
  pinMode(LeftMotorForward, OUTPUT);
  pinMode(LeftMotorBackward, OUTPUT);
  pinMode(RightMotorBackward, OUTPUT);
  
  servo_motor.attach(7); //our servo pin

  servo_motor.write(90);
  delay(2000);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
}


void loop() {


  int distanceRight = 0;
  int distanceLeft = 0;
  delay(50);

    if (distance <= 30){
    moveStop();
    delay(300);
    moveBackward();
    delay(400);
    moveStop();
    delay(1000);
    /*distanceRight = lookRight();
    delay(300);
    distanceLeft = lookLeft();
    delay(300);

    if (distance >= distanceLeft){
      turnRight();
      moveStop();
    }
    else{
      turnLeft();
      moveStop();
    }*/
  }
  else{
    moveForward(); 
  }
  distance = readPing();

    if (Serial.available() > 0) {

  incomingByte = Serial.readStringUntil('\n');
    if (incomingByte == "left") {
      Serial.write("Going Left");
      digitalWrite(4,LOW);
      digitalWrite(2,HIGH);
      delay(2000);
      digitalWrite(2,LOW);
      delay(1000);
    }

    else if (incomingByte == "right") {
      Serial.write("Going Right");
      digitalWrite(2,LOW);
      digitalWrite(4,HIGH);
      delay(2000);
      digitalWrite(4,LOW);   
      delay(1000);  
    }

  }

}

int lookRight(){  
  servo_motor.write(0);
  delay(500);
  int distance = readPing();
  delay(100);
  servo_motor.write(90);
  return distance;
}

int lookLeft(){
  servo_motor.write(180);
  delay(500);
  int distance = readPing();
  delay(100);
  servo_motor.write(90);
  return distance;
  delay(100);
}

int readPing(){
  delay(70);
  int cm = sonar.ping_cm();
  if (cm==0){
    cm=250;
  }
  return cm;
}

void moveStop(){
  
  digitalWrite(RightMotorForward, LOW);
  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(RightMotorBackward, LOW);
  digitalWrite(LeftMotorBackward, LOW);
}

void moveForward(){

  if(!goesForward){

    goesForward=true;
    
    digitalWrite(LeftMotorForward, HIGH);
    digitalWrite(RightMotorForward, HIGH);
    digitalWrite(LeftMotorBackward, LOW);
    digitalWrite(RightMotorBackward, LOW); 
  }
}

void moveBackward(){

  goesForward=false;

  digitalWrite(LeftMotorBackward, HIGH);
  digitalWrite(RightMotorBackward, HIGH);
  
  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(RightMotorForward, LOW);
  
}

void turnRight(){

  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(RightMotorForward, HIGH);
  delay(2500);
  digitalWrite(RightMotorForward, LOW);
  
}

void turnLeft(){

  digitalWrite(LeftMotorForward, HIGH);
  digitalWrite(RightMotorForward, LOW);
  delay(2100);
  digitalWrite(LeftMotorForward, LOW);
}
