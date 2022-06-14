#include<Arduino.h>
#include<Math.h>
#include<stdio.h>


/*******************************## 28BYJ-48 Stepper Motor 5V DC ##**********************************************
STEPPER MOTOR FULL STEP DRIVE WITH SINGLE PHASE (ONE STEP WITH SINGLE COIL ENERGISING)
 
 ## Created By Keerthan Suvarna - 11-06-2022, 10.33PM
 ## Simple illustration with out using any library function
 ## Here ULN2003AN IC is used to drive the stepper motor.
 ## Use external (5V - 12V) power supply to power ULN2003 IC as it draws around 300mA current even if the motor is in steady state.
 ## Connect Arduino GND to the External Powersupply GND.

 Note:
 1. One full rotation = 32 single steps
 2. One Step = 11.25 degree i.e, 32x11.25=360 degree
 3. One full rotation inclusive of gear set-up = 2037 steps (63.65:1 gear rayio---->63.65 x 32 = 2036.8)
 4. One Step = 0.176 degree (i.e, 0.176 x 2036.8 = 360)
 ################################ Code tested on ARDUINO UNO ################################################
******************************************************************************/

/* ######### Arduino Pin assigning & wire connections ##############*/

#define IN1 8  //Blue Wire
#define IN2 9  //Pink Wire
#define IN3 10 //Yellow Wire
#define IN4 11 //Orange Wire

/* ############## Parameters to count single steps and one complete rotation ##############*/

int step_count=0;
int i;
int rotation=0;

/*################### To command the direction at which motor should rotate #############################
CW ---> Make it True for Clock Wise rotation (Set CCW false to avoid conflict)
CCW --> Make it True for Conter Clock Wise rotation (Set CW false to avoid conflict)*/

bool CW = true;
bool CCW = false;

void setup() 
{
 Serial.begin(9600);
 
 pinMode(IN1, OUTPUT);
 pinMode(IN2, OUTPUT);
 pinMode(IN3, OUTPUT);
 pinMode(IN4, OUTPUT);

 digitalWrite(IN1, LOW);
 digitalWrite(IN2, LOW);
 digitalWrite(IN3, LOW);
 digitalWrite(IN4, LOW);
}

void loop()
{
/* ############## Code to rotate motor clock wise direction ##############*/
  if(CW)
  {
/* To select 4 coils of the motor indivisually and energise them alternatley using switch condition */
  for(i=1;i<=4;i++)
  {
    switch (i)
    {
      case 1:
               digitalWrite(IN1, HIGH);
               digitalWrite(IN2, LOW);
               digitalWrite(IN3, LOW);
               digitalWrite(IN4, LOW);
               step_count+=1;
               Serial.print("Coil :");
               Serial.print(i);
               delay(10);
               break;
      case 2: 
               digitalWrite(IN1, LOW);
               digitalWrite(IN2, HIGH);
               digitalWrite(IN3, LOW);
               digitalWrite(IN4, LOW);
               step_count+=1;
               Serial.print("Coil :");
               Serial.print(i);
               delay(10);
               break;

     case 3: 
               digitalWrite(IN1, LOW);
               digitalWrite(IN2, LOW);
               digitalWrite(IN3, HIGH);
               digitalWrite(IN4, LOW);
               step_count+=1;
               Serial.print("Coil :");
               Serial.print(i);
               delay(10);
               break;          

     case 4: 
               digitalWrite(IN1, LOW);
               digitalWrite(IN2, LOW);
               digitalWrite(IN3, LOW);
               digitalWrite(IN4, HIGH);
               step_count+=1;
               Serial.print("Coil :");
               Serial.print(i);
               delay(10);
               break;
     }
Serial.print("Steps Counted ---> ");
Serial.println(step_count);
//delay(10);
if(step_count % 2037 ==0)
{
rotation+=1;
Serial.print("Rotation Counted : ");
Serial.println(rotation);
delay(5000);

/*Uncomment below line to change the direction of the motor*/
CW=false;
CCW = true;

/*TO break the loop if 1 full rotation is completed*/
break;

  }
  }
  if(i==4)
 i=1;

}

 /* ############## Code to rotate motor counter clock wise direction ##############*/

 else if(CCW)
  {
  for(i=1;i<=4;i++)
  {
    switch (i)
    {
      case 1:
               digitalWrite(IN1, LOW);
               digitalWrite(IN2, LOW);
               digitalWrite(IN3, LOW);
               digitalWrite(IN4, HIGH);
               step_count+=1;
               Serial.print("Coil :");
               Serial.print(i);
               delay(10);
               break;
      case 2: 
               digitalWrite(IN1, LOW);
               digitalWrite(IN2, LOW);
               digitalWrite(IN3, HIGH);
               digitalWrite(IN4, LOW);
               step_count+=1;
               Serial.print("Coil :");
               Serial.print(i);
               delay(10);
               break;

     case 3: 
               digitalWrite(IN1, LOW);
               digitalWrite(IN2, HIGH);
               digitalWrite(IN3, LOW);
               digitalWrite(IN4, LOW);
               step_count+=1;
               Serial.print("Coil :");
               Serial.print(i);
               delay(10);
               break;          

     case 4: 
               digitalWrite(IN1, HIGH);
               digitalWrite(IN2, LOW);
               digitalWrite(IN3, LOW);
               digitalWrite(IN4, LOW);
               step_count+=1;
               Serial.print("Coil :");
               Serial.print(i);
               delay(10);
               break;
     }
Serial.print("Steps Counted : ");
Serial.println(step_count);
//delay(10);
if(step_count % 2037 ==0)
{
rotation+=1;
Serial.print("Rotation Counted : ");
Serial.println(rotation);
delay(5000);

 /*TO switch to CCW direction uncomment below lines*/
CCW=false;
CW=true;

/*TO break the loop if 1 full rotation is completed*/
break;

  }
  }
 if(i==4)
 i=1;

}
else
{
  Serial.println("Error!!!!Please initialise CW or CCW to true ");
}
}
