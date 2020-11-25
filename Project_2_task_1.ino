#include <Servo.h>
#define trig 12
#define echo 11 
#define ENABLE 5
#define DIRA 3
#define DIRB 4

int pos = 90;
int moveServo;
int X_pin = 0; 
int Y_pin = 1;
int neutral_X;
int neutral_Y;
double distance, duration;

Servo myservo;

void setup(){
  Serial.begin(9600);
  myservo.attach(9); 
  myservo.write(pos);
  neutral_Y=analogRead(Y_pin);
  neutral_X=analogRead(X_pin);
  pinMode(trig,OUTPUT);
  pinMode(echo,INPUT);
  pinMode(ENABLE,OUTPUT);
  pinMode(DIRA,OUTPUT);
  pinMode(DIRB,OUTPUT);
} 

void loop(){
  digitalWrite(DIRB,LOW);
  digitalWrite(DIRA,LOW);
  analogWrite(ENABLE,LOW);

  if(analogRead(X_pin)>neutral_X)
  {
    moveServo=map(analogRead(X_pin),-512,512,-90,90);
    myservo.write(moveServo);
    delay(10);
  }
  
  if(analogRead(X_pin)<neutral_X)
  {
    moveServo=map(analogRead(X_pin),-512,512,-90,90);
    myservo.write(moveServo);
    delay(10);
  }
  
  if(analogRead(Y_pin)>neutral_Y+50)
  {
    digitalWrite(DIRB,LOW);
    digitalWrite(DIRA,HIGH);
    analogWrite(ENABLE, map(analogRead(Y_pin),0,1023-neutral_Y,0,255));
    delay(50);
  }
  
  if(analogRead(Y_pin)<neutral_Y-50)
  {
    digitalWrite(DIRB,HIGH);
    digitalWrite(DIRA,LOW);
    analogWrite(ENABLE,map(analogRead(Y_pin),0,neutral_Y,0,255));
    delay(50);
  }

}

double dist_calc()
{
  digitalWrite(trig,LOW);
  delayMicroseconds(2);
  digitalWrite(trig,HIGH);
  delayMicroseconds(10);
  digitalWrite(trig,LOW);
  duration = pulseIn(echo,HIGH); 
  distance = 100.0*(343.0*(duration/2.0))/1000000.0; 
  return (distance);
}
