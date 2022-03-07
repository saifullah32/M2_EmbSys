#include <LiquidCrystal.h> 
#include<Servo.h> 

#define echo   2
#define trig   3
#define Buzzer 7
#define LED 4

const int scan_Distance = 50;

float  period; 
float distance;  
Servo myservo ;

LiquidCrystal lcd(13, 12, 11, 10, 9, 8);

void setup() {
  myservo.attach(6); 

  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(LED,OUTPUT);
  pinMode(Buzzer,OUTPUT);
  Serial.begin(9600);
  lcd.begin(16, 2);

}

void loop() {
  for (int i = 0; i <= 180; i++) 
  {  
    myservo.write(i);

    time_Measurement();

    distance = period * (0.0343) / 2; 
  
    if (distance <= scan_Distance)    
    {      
      person_detected();       
    }


    else {
      lcd.clear();
      lcd.print("Detecting...... ");
    }
    delay(100);
  }
  for (int i = 180; i >= 0; i--)   //servo motor rotates 180-0 degree
  {
    myservo.write(i);

    time_Measurement();

    distance = (float)period * (0.0343) / 2;


    if (distance <= scan_Distance) {
      person_detected();  
    }
    else {

      lcd.clear();
      lcd.print("Detecting...... ");

    }
    delay(100);
  }    
}

void time_Measurement()
{
  digitalWrite(trig, LOW);
  delayMicroseconds(2);

  digitalWrite(trig, HIGH);
  delayMicroseconds(10);


  digitalWrite(trig, LOW);


  period = pulseIn(echo, HIGH);
}