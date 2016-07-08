/*
 * IRremote: IRrecvDemo - demonstrates receiving IR codes with IRrecv
 * An IR detector/demodulator must be connected to the input RECV_PIN.
 * Version 0.1 July, 2009
 * Copyright 2009 Ken Shirriff
 * http://arcfn.com
 */

#include <IRremote.h>

// *** Infrared distance codes
#define ONOFF 18615
#define MODE 22695
#define MIRROR 30855
#define MENU -24481
#define LEFT_ARROW 8415
#define RIGHT_ARROW 24735
#define VIDEO -10201
#define DIMMER -2041
  
// *** Infrared values
const int irPin = 11;
IRrecv irReceiver(irPin);
decode_results results;
int irCode;
int storedIrCode = 0;

// *** Button values
const int buttonPin = 10;     // the number of the pushbutton pin
int buttonState;             // the current reading from the input pin
int lastButtonState = LOW;   // the previous reading from the input pin
// the following variables are long's because the time, measured in miliseconds,
// will quickly become a bigger number than can be stored in an int.
long lastDebounceTime = 0;  // the last time the output pin was toggled
long debounceDelay = 50;    // the debounce time; increase if the output flickers
int storedButtonState;

// *** Light values
const int lightPin_4 = 6;
const int lightPin_6 = 5;
int lightStatus = 0;

void setup()
{
  Serial.begin(9600);
  irReceiver.enableIRIn(); // Start the receiver
  pinMode(buttonPin, INPUT);
  pinMode(lightPin_4, OUTPUT);
  pinMode(lightPin_6, OUTPUT);
}

void loop()
{
// *** Infrared section
  if (irReceiver.decode(&results))
  {
    irCode = results.value;
    if ((irCode == -1) && ((storedIrCode == LEFT_ARROW) || (storedIrCode == RIGHT_ARROW)))
      irCode = storedIrCode;
    if (irCode != -1) 
    {

        if (irCode == ONOFF)
             if (lightStatus == 0)
             {
               lightStatus = 1;
               turnLights(lightStatus);  
             }
             else 
             {
               lightStatus = 0;
               turnLights(lightStatus);  
             } 
        if ((irCode == MODE) && (lightStatus != 0))
        {
          lightStatus = lightStatus + 1;
          if (lightStatus >3)
            lightStatus = 1; 
          turnLights(lightStatus);  
        }
      Serial.print(irCode);
      Serial.print(" - "); 
      Serial.println(lightStatus);
    }
    storedIrCode = irCode;  
    irReceiver.resume(); // Receive the next value
  }
// *** Button section
  
  int reading = digitalRead(buttonPin);               // read the state of the switch into a local variable:
  if (reading != lastButtonState)                     // If the switch changed, due to noise or pressing:
    lastDebounceTime = millis();                      // reset the debouncing timer
  if ((millis() - lastDebounceTime) > debounceDelay)  // whatever the reading is at, it's been there for longer
    buttonState = reading;      // than the debounce delay, so take it as the actual current state:
  if ((buttonState == HIGH) && (buttonState != storedButtonState)) 
    {
      lightStatus = lightStatus + 1;
      if (lightStatus >3)
        lightStatus = 0; 
      turnLights(lightStatus);  
      Serial.print(buttonState); 
      Serial.print(" - "); 
      Serial.println(lightStatus);
    }
  storedButtonState = buttonState;  
  lastButtonState = reading;        // save the reading.  Next time through the loop, it'll be the lastButtonState:
}


void turnLights(int S)
{
      switch (S)
      {
        case 0: {
                  digitalWrite(lightPin_4, LOW);
                  digitalWrite(lightPin_6, LOW);
                  break;
                }
        case 1: {
                  digitalWrite(lightPin_4, HIGH);
                  digitalWrite(lightPin_6, LOW);
                  break;
                }
        case 2: {
                  digitalWrite(lightPin_4, LOW);
                  digitalWrite(lightPin_6, HIGH);
                  break;
                }
        case 3: {
                  digitalWrite(lightPin_4, HIGH);
                  digitalWrite(lightPin_6, HIGH);
                  break;
                }
      }
  
}
