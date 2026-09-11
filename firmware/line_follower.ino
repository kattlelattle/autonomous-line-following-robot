#define IR_R A0
#define IR_MR A1
#define IR_M A2
#define IR_ML A3
#define IR_L A4

#include <math.h>
#include <Adafruit_MotorShield.h>
#include <stdio.h>

// Motor A
const int ENA = 5;   // PWM
const int IN1 = 6;
const int IN2 = 9;

// Motor B
const int ENB = 10;  // PWM
const int IN3 = 11;
const int IN4 = 12;

void setup() {
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  stopMotors();

  pinMode(IR_R, INPUT);
  pinMode(IR_MR, INPUT);
  pinMode(IR_M, INPUT);
  pinMode(IR_ML, INPUT);
  pinMode(IR_L, INPUT);
  
  Serial.begin(9600);
}

void loop() {
  bool r, mr, m, ml, l;
  r = digitalRead(IR_R);
  mr = digitalRead(IR_MR);
  m = digitalRead(IR_M);
  ml = digitalRead(IR_ML);
  l = digitalRead(IR_L);

  Serial.print(r);
  Serial.print(mr);
  Serial.print(m);
  Serial.print(ml);
  Serial.println(l);

  if(!r && !mr && !m && !ml && !l){
    stopMotors();
  }
  else if(r && mr && m && ml && l){
    stopMotors();
  }
  else if(!r && mr && ml && !l){ //forward
    motorA(100);
    motorB(100);
  }
  else if(!r && mr && ml && l){ //left
    motorA(255);
    motorB(20);
  }
  else if(!r && !mr && ml && l){ //sharp left
    motorA(255);
    motorB(0);
  }
  else if(r && ml && !l){ //right
    motorA(20);
    motorB(255);
  }
  else if(r && !ml && !l){ //sharp right
    motorA(0);
    motorB(255);
  }
  else{
    motorA(100);
    motorB(100);
  }
}

void motorA(int speed) {
  if (speed > 0) {
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    analogWrite(ENA, speed);
  }
  else if (speed < 0) {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    analogWrite(ENA, -speed);
  }
  else {
    analogWrite(ENA, 0);
  }
}

void motorB(int speed) {
  if (speed > 0) {
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
    analogWrite(ENB, speed);
  }
  else if (speed < 0) {
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    analogWrite(ENB, -speed);
  }
  else {
    analogWrite(ENB, 0);
  }
}

void stopMotors() {
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}