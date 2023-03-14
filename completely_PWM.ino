#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <Servo.h> 
#define D0 2
#define D1 3
#define D2 4
#define D3 5
#define s 9
#define SERVOMIN  125 // this is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  575 // this is the 'maximum' pulse length count (out of 4096)
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x47); // PCA9685 bus address 
int speeds = 1000;
int angle1 = 0;
int angle2 = 100;
int angle3 = 45;

void setup() {
  pinMode(D0, INPUT);
  pinMode(D1, INPUT);
  pinMode(D2, INPUT);
  pinMode(D3, INPUT);
  pinMode(s, INPUT);
  Serial.begin(9600);
  pwm.begin();
  pwm.setPWMFreq(60);
}
 void forward()     // going forwards
{ 
  pwm.setPWM(0, 0, 4095);
  pwm.setPWM(1, 0, speeds);
  pwm.setPWM(2, 0, 4095);
  pwm.setPWM(3, 0, speeds);
  pwm.setPWM(4, 0, 4095);
  pwm.setPWM(5, 0, speeds);
  pwm.setPWM(6, 0, 4095);
  pwm.setPWM(7, 0, speeds);
}
void right()
{ 
  pwm.setPWM(0, 0, 4095);
  pwm.setPWM(1, 0, speeds);
  pwm.setPWM(2, 0, 0);
  pwm.setPWM(3, 0, speeds);
  pwm.setPWM(4, 0, 0);
  pwm.setPWM(5, 0, speeds);
  pwm.setPWM(6, 0, 4059);
  pwm.setPWM(7, 0, speeds);
  
}
void left()
{ 
  pwm.setPWM(0, 0, 0);
  pwm.setPWM(1, 0, speeds);
  pwm.setPWM(2, 0, 4095);
  pwm.setPWM(3, 0, speeds);
  pwm.setPWM(4, 0, 4095);
  pwm.setPWM(5, 0, speeds);
  pwm.setPWM(6, 0, 0);
  pwm.setPWM(7, 0, speeds);
}
void stopp()         //stop
{ 
  pwm.setPWM(1, 0, 0);
  pwm.setPWM(2, 0, 0);
  pwm.setPWM(3, 0, 0);
  pwm.setPWM(4, 0, 0);
  pwm.setPWM(5, 0, 0);
  pwm.setPWM(6, 0, 0);
  pwm.setPWM(7, 0, 0);
}
void backward()          //back
{ 
  pwm.setPWM(0, 0, 0);
  pwm.setPWM(1, 0, speeds);
  pwm.setPWM(2, 0, 0);
  pwm.setPWM(3, 0, speeds);
  pwm.setPWM(4, 0, 0);
  pwm.setPWM(5, 0, speeds);
  pwm.setPWM(6, 0, 0);
  pwm.setPWM(7, 0, speeds);
}

int angleToPulse(int ang){
   int pulse = map(ang,0, 180, SERVOMIN,SERVOMAX);// map angle of 0 to 180 to Servo min and Servo max 
   Serial.print("Angle: ");Serial.print(ang);
   Serial.print(" pulse: ");Serial.println(pulse);
   return pulse;
}


void gripper_open()
{
   if(angle3<180)

    {
      angle3=angle3+30;
      pwm.setPWM(8, 0, angleToPulse(angle3) );
      delay(500);
    }                      
}
void gripper_close()
{
 
  if(angle3>0)
  { 
    angle3 = angle3-30;
    pwm.setPWM(8, 0, angleToPulse(angle3) );
    delay(500);
  }
}

void elbow_down()
{
  if(angle2>0)
  { 
    angle2 = angle2-45;
    pwm.setPWM(9, 0, angleToPulse(angle2) );
    delay(500);
  }
}
void elbow_up()
{
   if(angle2<180)
    {
      angle2=angle2+45;
      pwm.setPWM(9, 0, angleToPulse(angle2) );
      delay(500);
    }
}
  
void base_right()
{ 
  if(angle1>0)
  { 
    angle1 = angle1-45;
    pwm.setPWM(10, 0, angleToPulse(angle1) );
    delay(500);
  }
}

void base_left()
{
  if(angle1<180)
    {
      angle1=angle1+45;
      pwm.setPWM(10, 0, angleToPulse(angle1) );
      delay(500);
    }
}

void loop() {
  while(digitalRead(s) == 0 )

  {stopp();}
  
  while(digitalRead(s) == 1 && digitalRead(D0)==1 && digitalRead(D1)==0 && digitalRead(D2)==1 && digitalRead(D3)==0)
  
  {stopp();}

  while(digitalRead(s) == 1 && digitalRead(D0)==0 && digitalRead(D1)==1 && digitalRead(D2)==0 && digitalRead(D3)==0)

  {forward();}

  while(digitalRead(s) == 1 && digitalRead(D0)==0 && digitalRead(D1)==0 && digitalRead(D2)==1 && digitalRead(D3)==0)

  {left();}

  while(digitalRead(s) == 1 && digitalRead(D0)==0 && digitalRead(D1)==1 && digitalRead(D2)==1 && digitalRead(D3)==0)

  {right();}

  while(digitalRead(s) == 1 && digitalRead(D0)==0 && digitalRead(D1)==0 && digitalRead(D2)==0 && digitalRead(D3)==1)

  {backward();}
  
  while(digitalRead(s) == 1 && digitalRead(D0)==1 && digitalRead(D1)==0 && digitalRead(D2)==0 && digitalRead(D3)==0)

  {gripper_open();}

  while(digitalRead(s) == 1 && digitalRead(D0)==1 && digitalRead(D1)==1 && digitalRead(D2)==0 && digitalRead(D3)==0)

  {gripper_close();}

  while(digitalRead(s) == 1 && digitalRead(D0)==1 && digitalRead(D1)==0 && digitalRead(D2)==0 && digitalRead(D3)==1)

  {elbow_down();}

  while(digitalRead(s) == 1 && digitalRead(D0)==1 && digitalRead(D1)==1 && digitalRead(D2)==1 && digitalRead(D3)==0)

  {elbow_up();}

  while(digitalRead(s) == 1 && digitalRead(D0)==1 && digitalRead(D1)==1 && digitalRead(D2)==0 && digitalRead(D3)==1)
  
  {base_right();}
  
  while(digitalRead(s) == 1 && digitalRead(D0)==0 && digitalRead(D1)==0 && digitalRead(D2)==1 && digitalRead(D3)==1)
  
  {base_left();}
}
