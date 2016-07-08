#include <Bounce.h>

#define btnONOFF  11
#define btnSELECT 10

#define speedOne   3
#define speedTwo   4
#define speedThree 5

// *** ON/OFF Button values
Bounce btnOnOffBounce = Bounce( btnONOFF, 50); 
boolean btnOnOffState = false;

// *** SELECT Button values
Bounce btnSelectBounce = Bounce( btnSELECT, 50); 

// *** Speed values
int outState = 1;

void setup()
{
  Serial.begin(9600);
  pinMode(btnONOFF, INPUT);
  pinMode(btnSELECT, INPUT);
  pinMode(speedOne, OUTPUT);
  pinMode(speedTwo, OUTPUT);
  pinMode(speedThree, OUTPUT);
  turnSpeed(0);
}

void loop()
{
// *** ON/OFF Button section 
  if (btnOnOffBounce.update())
       if (btnOnOffBounce.risingEdge())
         {
           btnOnOffState = !btnOnOffState;
           digitalWrite(13, btnOnOffState);
           turnSpeed(outState - !btnOnOffState * outState);
         } 

// *** SELECT Button section
  if (btnSelectBounce.update() && btnOnOffState)
       if (btnSelectBounce.risingEdge()) 
         {
           outState = outState + 1;
           if (outState > 3)
             outState = 1; 
           turnSpeed(outState);  
         }
}


void turnSpeed(int S)
{
      switch (S)
      {
        case 0: {
                  digitalWrite(speedOne, LOW);
                  digitalWrite(speedTwo, LOW);
                  digitalWrite(speedThree, LOW);
                  break;
                }
        case 1: {
                  digitalWrite(speedOne, HIGH);
                  digitalWrite(speedTwo, LOW);
                  digitalWrite(speedThree, LOW);
                  break;
                }
        case 2: {
                  digitalWrite(speedOne, LOW);
                  digitalWrite(speedTwo, HIGH);
                  digitalWrite(speedThree, LOW);
                  break;
                }
        case 3: {
                  digitalWrite(speedOne, LOW);
                  digitalWrite(speedTwo, LOW);
                  digitalWrite(speedThree, HIGH);
                  break;
                }
      }
  
}
