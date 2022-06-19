#include<Arduino.h>
#include<Math.h>
#include<stdio.h>


/*******************************## 28BYJ-48 Stepper Motor 5V DC ##**********************************************
  3. STEPPER MOTOR HALF STEP DRIVE

  ## Created By Keerthan Suvarna - 11-06-2022, 10.33PM
  ## Simple illustration with out using any library function
  ## Here ULN2003AN IC is used to drive the stepper motor.
  ## Use external (5V - 12V) power supply to power ULN2003 IC as it draws around 300mA current even if the motor is in steady state.
  ## Connect Arduino GND to the External Powersupply GND.

  Note:
  1. One full rotation = 64 single steps
  2. One Step = 5.625 degree i.e, 64x5.625=360 degree
  3. One full rotation inclusive of gear set-up = 4073.6 steps (63.65:1 gear ratio---->63.65 x 64 = 4073.6)
  4. One Step = 0.0883 degree (i.e, 0.0883 x 4073.6 = 360)
  5. Torque is less compare to full step two phase drive but more than full step single phase drive.
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

/*################### To determine direction at which motor should rotate #############################
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
  if (CW)
  {
    /* To select 4 coils of the motor indivisually and energise them alternatley using switch condition */
    for (i = 1; i <= 8; i++)
    {
      switch (i)
      {
        case 1:
          digitalWrite(IN1, HIGH);
          digitalWrite(IN2, LOW);
          digitalWrite(IN3, LOW);
          digitalWrite(IN4, LOW);
          step_count += 1;
          delay(10);
          break;
        case 2:
          digitalWrite(IN1, HIGH);
          digitalWrite(IN2, HIGH);
          digitalWrite(IN3, LOW);
          digitalWrite(IN4, LOW);
          step_count += 1;
          delay(10);
          break;

        case 3:
          digitalWrite(IN1, LOW);
          digitalWrite(IN2, HIGH);
          digitalWrite(IN3, LOW);
          digitalWrite(IN4, LOW);
          step_count += 1;
          delay(10);
          break;

        case 4:
          digitalWrite(IN1, LOW);
          digitalWrite(IN2, HIGH);
          digitalWrite(IN3, HIGH);
          digitalWrite(IN4, LOW);
          step_count += 1;
          delay(10);
          break;

        case 5:
          digitalWrite(IN1, LOW);
          digitalWrite(IN2, LOW);
          digitalWrite(IN3, HIGH);
          digitalWrite(IN4, LOW);
          step_count += 1;
          delay(10);
          break;

        case 6:
          digitalWrite(IN1, LOW);
          digitalWrite(IN2, LOW);
          digitalWrite(IN3, HIGH);
          digitalWrite(IN4, HIGH);
          step_count += 1;
          delay(10);
          break;

        case 7:
          digitalWrite(IN1, LOW);
          digitalWrite(IN2, LOW);
          digitalWrite(IN3, LOW);
          digitalWrite(IN4, HIGH);
          step_count += 1;
          delay(10);
          break;

        case 8:
          digitalWrite(IN1, HIGH);
          digitalWrite(IN2, LOW);
          digitalWrite(IN3, LOW);
          digitalWrite(IN4, HIGH);
          step_count += 1;
          delay(10);
          break;

      }

      //Serial.print("Steps Counted (CW) ");
      //Serial.println(step_count);
      //delay(10);


      if (step_count % 4074 == 0)
      {
        rotation += 1;
        Serial.print("Rotation Counted : ");
        Serial.println(rotation);
        delay(1000);

        /*TO switch to CCW direction uncomment below lines*/
        CW = false;
        CCW = true;


        /*TO break the loop if 1 full rotation is completed*/
        break;
      }
    }
    if (i == 8)
    {
      i = 1;
    }
  }

  /* ############## Code to rotate motor counter clock wise direction ##############*/

  else if (CCW)
  {
    for (i = 1; i <= 8; i++)
    {
      switch (i)
      {
        case 1:
          digitalWrite(IN1, LOW);
          digitalWrite(IN2, LOW);
          digitalWrite(IN3, LOW);
          digitalWrite(IN4, HIGH);
          step_count += 1;
          delay(10);
          break;
        case 2:
          digitalWrite(IN1, LOW);
          digitalWrite(IN2, LOW);
          digitalWrite(IN3, HIGH);
          digitalWrite(IN4, HIGH);
          step_count += 1;
          delay(10);
          break;

        case 3:
          digitalWrite(IN1, LOW);
          digitalWrite(IN2, LOW);
          digitalWrite(IN3, HIGH);
          digitalWrite(IN4, LOW);
          step_count += 1;
          delay(10);
          break;

        case 4:
          digitalWrite(IN1, LOW);
          digitalWrite(IN2, HIGH);
          digitalWrite(IN3, HIGH);
          digitalWrite(IN4, LOW);
          step_count += 1;
          delay(10);
          break;

        case 5:
          digitalWrite(IN1, LOW);
          digitalWrite(IN2, HIGH);
          digitalWrite(IN3, LOW);
          digitalWrite(IN4, LOW);
          step_count += 1;
          delay(10);
          break;

        case 6:
          digitalWrite(IN1, HIGH);
          digitalWrite(IN2, HIGH);
          digitalWrite(IN3, LOW);
          digitalWrite(IN4, LOW);
          step_count += 1;
          delay(10);
          break;

        case 7:
          digitalWrite(IN1, LOW);
          digitalWrite(IN2, HIGH);
          digitalWrite(IN3, LOW);
          digitalWrite(IN4, LOW);
          step_count += 1;
          delay(10);
          break;

        case 8:
          digitalWrite(IN1, HIGH);
          digitalWrite(IN2, LOW);
          digitalWrite(IN3, LOW);
          digitalWrite(IN4, HIGH);
          step_count += 1;
          delay(10);
          break;


      }

      //Serial.print("Steps Counted (CCW): ");
      //Serial.println(step_count);
      //delay(10);
      if (step_count % 4074 == 0)
      {
        rotation += 1;
        Serial.print("Rotation Counted : ");
        Serial.println(rotation);
        delay(1000);

        /*TO switch to CW direction uncomment below lines*/
        CCW = false;
        CW = true; break;

        /*TO break the loop if 1 full rotation is completed*/
        break;

      }
    }
    if (i == 8)
    {
      i = 1;
    }
  }
  else
  {
    Serial.println("Error!!!!Please initialise any direction to true ");
  }
}
