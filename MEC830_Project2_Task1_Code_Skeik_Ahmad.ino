//MEC830_Project2_Task1:

//Include Libraries for servo, stepper and IR Remote: 
  #include <Servo.h>
  #include "Stepper.h"
  #include "IRremote.h"

//Define Variables:
  #define STEPS  32   
  #define trig 4
  #define echo 5 
  int  Steps2Take;  
  int receiver = 12; 
  int pos=89;
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
  myservo.write(pos);
  if (irrecv.decode(&results)) // have we received an IR signal?

  {
    Serial.println(results.value,HEX);
    switch(results.value)

    {

      case 0xFFA857: // Forward
                      small_stepper.setSpeed(500);
                      Steps2Take  =  4800;  
                      small_stepper.step(Steps2Take);
                      delay(30); 
                      break;
                      
      case 0xFF629D: // Backward
                      small_stepper.setSpeed(500); 
                      Steps2Take  =  -4800;  
                      small_stepper.step(Steps2Take);
                      delay(30); 
                      break;

      case 0xFFC23D: //Move right
                      myservo.write(165);
                      small_stepper.setSpeed(500);
                      Steps2Take = -480;
                      small_stepper.step(Steps2Take);
                      delay(30);
                      break;

      case 0xFF22DD: //Move left
                      myservo.write(15);
                      small_stepper.setSpeed(500);
                      Steps2Take = -480;
                      small_stepper.step(Steps2Take);
                      delay(30);
                      break;
                
    }
    
      irrecv.resume(); // receive the next value
                 digitalWrite(8, LOW);
                 digitalWrite(9, LOW);
                 digitalWrite(10, LOW);
                 digitalWrite(11, LOW);       
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
