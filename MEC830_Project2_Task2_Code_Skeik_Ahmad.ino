//MEC830_Project2_Task2:

//Include Libraries for servo, stepper and IR Remote: 
  #include <Servo.h>
  #include "Stepper.h"
  #include "IRremote.h"
  
//Define Variables:
  #define STEPS  32   
  #define trig 4
  #define echo 5 
  int Steps2Take;  
  int receiver = 12; 
  int pos=88.5;
  double duration, distance;

//Called functions from included libraries:
  Stepper small_stepper(STEPS, 8, 10, 9, 11);
  Servo myservo;
  IRrecv irrecv(receiver);    
  decode_results results;    

void setup()
{ 
  Serial.begin(9600);
  irrecv.enableIRIn(); 
  Serial.begin(9600); 
  myservo.attach(6); 
  myservo.write(pos);
  pinMode(trig,OUTPUT);
  pinMode(echo,INPUT);
}

void loop()
{
  small_stepper.setSpeed(500);
  
  //go straight
  myservo.write(pos);
  small_stepper.step(-9500);
  delay(10);
  
  //turn right
  myservo.write(165);
  small_stepper.step(-2000);
  delay(10);

  //go straight
  myservo.write(88.5);
  small_stepper.step(-9500);
  delay(10);

  //turn left
  myservo.write(15);
  small_stepper.step(-2250);
  delay(10);

  //go straight
  myservo.write(88.5);
  small_stepper.step(-9500);
  delay(10);
  
while(1)//endless loop
{
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
