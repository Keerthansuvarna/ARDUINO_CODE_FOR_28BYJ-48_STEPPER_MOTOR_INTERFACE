#include<Arduino.h>
#include<Math.h>
#include<stdio.h>

/*******************************## 28BYJ-48 Stepper Motor 5V DC ##*************************************************/

/*******************************## Code for Speed Control  ##***********************************************


  STEPPER MOTOR FULL STEP DRIVE WITH SINGLE PHASE (ONE STEP WITH SINGLE COIL ENERGISING)

  ## Created By Keerthan Suvarna - 14-06-2022, 10.58PM
  ## Simple illustration with out using any library function
  ## Here ULN2003AN IC is used to drive the stepper motor.
  ## Use external (5V - 12V) power supply to power ULN2003 IC as it draws around 300mA current even if the motor is in steady state.
  ## Connect Arduino GND to the External Powersupply GND.

  Note:
  1. One full rotation = 32 single steps
  2. One Step = 11.25 degree i.e, 32x11.25=360 degree
  3. One full rotation inclusive of gear set-up = 2037 steps (63.65:1 gear rayio---->63.65 x 32 = 2036.8)
  4. One Step = 0.176 degree (i.e, 0.176 x 2036.8 = 360)

  ################################ Calculation for Rotation Per Minute (RPM) ################################################
    For 30 millisecond delay ---> ~ 01.0 RPM (Considering 01 rpm)
    For 10 millisecond delay ---> ~ 03.0 RPM (Considering 03 rpm)
    For 02 millisecond delay ---> ~ 14.5 RPM (Considering 14 rpm)

  ################################ Code tested on ARDUINO UNO ################################################
******************************************************************************/

/* ######### Arduino Pin assigning & wire connections ##############*/

#define IN1 8  //Blue Wire
#define IN2 9  //Pink Wire
#define IN3 10 //Yellow Wire
#define IN4 11 //Orange Wire

/* ############## Parameters to count single steps and one complete rotation ##############*/

int step_count = 0;
int i;
int rotation = 0;

/*################### To command the direction at which motor should rotate #############################
  CW ---> Make it True for Clock Wise rotation (Set CCW false to avoid conflict)
  CCW --> Make it True for Conter Clock Wise rotation (Set CW false to avoid conflict)*/

bool CW = true;
bool CCW = false;

/*################### To command the speed at which motor should rotate #############################*/

float start_speed = 1;    // RPM           --->   Minimum = 1 & Maximum = 14 (Do not exceed theese value...will cause damage to the Stepper Motor)
float accelaration = 0.1; // Change in RPM --->   Change this value in which step the accelation has to increase (Recommended less than 1)
float set_rpm_delay = 0;  // Do not change this value!!!
float temp = 0;           // Do not change this value!!!


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

  /*################### Testing for rpm is out of desired range #############################*/

  if (start_speed <= 0)
  {
    start_speed = 1;
  }

  else if (start_speed > 14)

  {
    start_speed = 14;
  }

  /*################### Testing for rpm is out of desired range #############################*/

  if (accelaration >= 1 || accelaration <= 0)

  {
    accelaration = 0.1; // Setting accelaration to 1
  }

  /* ############## Converting rpm into delay ##############*/

  if (start_speed == 14)
  {
    set_rpm_delay = 2;
    temp = set_rpm_delay;
  }

  else
  {
    set_rpm_delay = map(start_speed, 1, 14, 30, 2 );
    temp = set_rpm_delay;
  }
}

void loop()
{

  /* ############## Code to rotate motor clock wise direction ##############*/

  if (CW)
  {
    /* To select 4 coils of the motor indivisually and energise them alternatley using switch condition */
    for (i = 1; i <= 4; i++)
    {
      switch (i)
      {
        case 1:
          digitalWrite(IN1, HIGH);
          digitalWrite(IN2, LOW);
          digitalWrite(IN3, LOW);
          digitalWrite(IN4, LOW);
          step_count += 1;
          delay(set_rpm_delay);
          break;

        case 2:
          digitalWrite(IN1, LOW);
          digitalWrite(IN2, HIGH);
          digitalWrite(IN3, LOW);
          digitalWrite(IN4, LOW);
          step_count += 1;
          delay(set_rpm_delay);
          break;

        case 3:
          digitalWrite(IN1, LOW);
          digitalWrite(IN2, LOW);
          digitalWrite(IN3, HIGH);
          digitalWrite(IN4, LOW);
          step_count += 1;
          delay(set_rpm_delay);
          break;

        case 4:
          digitalWrite(IN1, LOW);
          digitalWrite(IN2, LOW);
          digitalWrite(IN3, LOW);
          digitalWrite(IN4, HIGH);
          step_count += 1;
          accelarate_rpm();
          break;
      }

      //      Serial.println(set_rpm_delay);
      //      Serial.print("Steps Counted ---> ");
      //      Serial.println(step_count);
      //      delay(10);

      if (step_count % 2037 == 0)
      {
        rotation += 1;
        Serial.print("Rotation Counted : ");
        Serial.println(rotation);
        delay(1000);

        /*Uncomment below line to change the direction of the motor*/
        CW = false;
        CCW = true;

        /*To reset the set_rpm_delay value to default*/
        set_rpm_delay = temp;

        /*TO break the loop if 1 full rotation is completed*/
        break;
      }
    }
    if (i == 4)
      i = 1;

  }
  /* ############## Code to rotate motor counter clock wise direction ##############*/

  else if (CCW)
  {
    for (i = 1; i <= 4; i++)
    {
      switch (i)
      {
        case 1:
          digitalWrite(IN1, LOW);
          digitalWrite(IN2, LOW);
          digitalWrite(IN3, LOW);
          digitalWrite(IN4, HIGH);
          step_count += 1;
          delay(set_rpm_delay);
          break;

        case 2:
          digitalWrite(IN1, LOW);
          digitalWrite(IN2, LOW);
          digitalWrite(IN3, HIGH);
          digitalWrite(IN4, LOW);
          step_count += 1;
          delay(set_rpm_delay);
          break;
        case 3:
          digitalWrite(IN1, LOW);
          digitalWrite(IN2, HIGH);
          digitalWrite(IN3, LOW);
          digitalWrite(IN4, LOW);
          step_count += 1;
          delay(set_rpm_delay);
          break;

        case 4:
          digitalWrite(IN1, HIGH);
          digitalWrite(IN2, LOW);
          digitalWrite(IN3, LOW);
          digitalWrite(IN4, LOW);
          step_count += 1;
          accelarate_rpm();
          break;
      }

//      Serial.println(set_rpm_delay);
//      Serial.print("Steps Counted : ");
//      Serial.println(step_count);
//      delay(10);

      if (step_count % 2037 == 0)
      {
        rotation += 1;
        Serial.print("Rotation Counted : ");
        Serial.println(rotation);
        delay(1000);

        /*TO switch to CCW direction uncomment below lines*/
        CCW = false;
        CW = true;

       /*To reset the set_rpm_delay value to default*/
        set_rpm_delay = temp;

        /*TO break the loop if 1 full rotation is completed*/
        break;

      }
    }
    if (i == 4)
      i = 1;

  }
  else
  {
    Serial.println("Error!!!!Please initialise CW or CCW to true ");
  }
}

void accelarate_rpm()
{
  if (set_rpm_delay <= 2)
  {
    set_rpm_delay = 2;
    delay(set_rpm_delay);
  }
  else
  {
    set_rpm_delay -= accelaration;
    delay(set_rpm_delay);
  }
}
