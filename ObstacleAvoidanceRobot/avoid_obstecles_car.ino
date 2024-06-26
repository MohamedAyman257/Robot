#include "BluetoothSerial.h"


BluetoothSerial SerialBT; 


//init value for blutooth
String BlueValue = "1";

// Left Motor
int IN1 = 27; 
int IN2 = 26; 
int motorLSpeed = 14; 

//Right Motor
int IN3 = 4; 
int IN4 = 2; 
int motorRSpeed = 15;

// Setting PWM properties
const int freq = 30000;
const int pwmChannel_0 = 0;   //for left motor
const int pwmChannel_1 = 1;  //for right motor
const int resolution = 8;
int dutyCycle = 190;

//IR sensor
int IRsensor =13;
int sensor_reading = 1; 



void setup() 
{
  // sets the pins as outputs:
    //left motor
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(motorLSpeed, OUTPUT);
    //Right motor
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(motorRSpeed, OUTPUT); 
  
   
  // configure LED PWM functionalitites
  ledcSetup(pwmChannel_0, freq, resolution);
  ledcSetup(pwmChannel_1, freq, resolution);
  
  // attach the channel to the GPIO to be controlled
  ledcAttachPin(motorLSpeed, pwmChannel_0);
  ledcAttachPin(motorRSpeed, pwmChannel_1);
  
  //Bluetooth Control
  Serial.begin(115200);
  SerialBT.begin("MY_CAR");

}

/*
 * function to send Robot forward by:
 * sending HIGH signal to left and Right motors
 */
void forward()
{digitalWrite(IN1,1);
 digitalWrite(IN2,0);
 digitalWrite(IN3,0);
 digitalWrite(IN4,1);
 ledcWrite(pwmChannel_0, dutyCycle);
 ledcWrite(pwmChannel_1, dutyCycle);
}

/*
 * function to send Robot backward by:
 * sending HIGH signal to left and Right motors BUT:
 * in reverse directions
 */
void backward()
{
  digitalWrite(IN1,0);
 digitalWrite(IN2,1);
 digitalWrite(IN3,1);
 digitalWrite(IN4,0);
 ledcWrite(pwmChannel_0, dutyCycle);
 ledcWrite(pwmChannel_1, dutyCycle);
}
/*
 * function to send Robot in Right direction by:
 * sending LOW signal to left and HIGH signal to Right motors
 */

void right()
{ 
  digitalWrite(IN1,1);
 digitalWrite(IN2,0);
 digitalWrite(IN3,0);
 digitalWrite(IN4,0);
 ledcWrite(pwmChannel_0, dutyCycle);
 ledcWrite(pwmChannel_1, 0);
}

/*
 * function to send Robot in Left direction by:
 * sending HIGH signal to left and LOW signal to Right motors
 */

void left()
{digitalWrite(IN1,0);
 digitalWrite(IN2,0);
 digitalWrite(IN3,0);
 digitalWrite(IN4,1);
 ledcWrite(pwmChannel_0, 0);
 ledcWrite(pwmChannel_1, dutyCycle);
}

/*
 * function to stop movement:
 * sending LOW signal to left and Right motors
 */
void stopp()
{digitalWrite(IN1,0);
 digitalWrite(IN2,0);
 digitalWrite(IN3,0);
 digitalWrite(IN4,0);
 ledcWrite(pwmChannel_0, 0);
 ledcWrite(pwmChannel_1, 0);
}

void loop() 
{
  if(SerialBT.available())
  {
    BlueValue= SerialBT.readString();
//Serial.println(BlueValue);
  }
    
  if(BlueValue == "0" || BlueValue == "start")
  { 
    sensor_reading =digitalRead(IRsensor); //update reading sensor value 
    //Serial.println(sensor_reading);
  
    if(sensor_reading == LOW)    //"0" ---> start
    {
      
      stopp();
      delay(500);   // stop time 
      backward();
      delay(500);  //backward time
      right();
      delay(250);  //Right direction time(***NEED TO BE TESTED***) 
      
    }
    else  
    {
      forward(); 
     
    }
  }
  else if(BlueValue == "1" || BlueValue == "stop")   //"1" ---> stop
  {
    stopp();
  }
      
  delay(20); 
      
}
