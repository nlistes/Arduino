/*
AC Voltage dimmer with Zero cross detection
Author: Charith Fernanado http://www.inmojo.com
License: Creative Commons Attribution Share-Alike 3.0 License. 

Attach the Zero cross pin of the module to Arduino External Interrupt pin
Select the correct Interrupt # from the below table:
(the Pin numbers are digital pins, NOT physical pins:
digital pin 2 [INT0]=physical pin 4 
and digital pin 3 [INT1]= physical pin 5)

 Pin    |  Interrrupt # | Arduino Platform
 ---------------------------------------
 2      |  0            |  All
 3      |  1            |  All
 18     |  5            |  Arduino Mega Only
 19     |  4            |  Arduino Mega Only
 20     |  3            |  Arduino Mega Only
 21     |  2            |  Arduino Mega Only

In the program pin 2 is chosen
 */

int AC_LOAD = 10;    // Output to Opto Triac pin
static word value;  // Value for handle input

// Due to timing problems, the use of ‘0’ can sometimes make the circuit 
// flicker. It is safer to use a value slightly higher than ‘0’

volatile int dimming = 0; // NAURIS: Dimming level (0-100)  0 = ON, 100 = OFF
volatile int dimtime = (100*dimming);
volatile word openshift = 3300, opendelay = 8;

void printVariables()
{
  Serial.print("     di(m)ming: ");
  Serial.println(dimming);
  Serial.print("     dimtime: ");
  Serial.println(dimtime);
  Serial.print("     open(s)hift: ");
  Serial.println(openshift);
  Serial.print("     open(d)elay: ");
  Serial.println(opendelay);
  Serial.println();
  
};

void setup()
{
  Serial.begin(57600);
  Serial.println("Initial variables");
  printVariables();
  pinMode(AC_LOAD, OUTPUT);// Set AC Load pin as output

  attachInterrupt(0, zero_crosss_int, RISING);  // Chooses '0' as interrupt for the zero-crossing
}

// the interrupt function must take no parameters and return nothing
void zero_crosss_int()  // function to be fired at the zero crossing to dim the light
{
  // Firing angle calculation : 1 full 50Hz wave =1/50=20ms  
  // Every zerocrossing thus: (50Hz)-> 10ms (1/2 Cycle) For 60Hz => 8.33ms
  // 10ms=10000us
  // (10000us - 10us) / 128 = 75 (Approx) For 60Hz =>65
  //int dimtime = (75*dimming);    // For 60Hz =>65     
  // NAURIS: (10000us - 10us) / 100 = 99.9 (100)
  
  //noInterrupts();
  delayMicroseconds(openshift);
  delayMicroseconds(dimtime);    // Off cycle
  digitalWrite(AC_LOAD, HIGH);   // triac firing
  delayMicroseconds(opendelay);         // triac On propogation delay
  digitalWrite(AC_LOAD, LOW);    // triac Off
  //interrupts();
}

void loop()  
{
  if (Serial.available())
  {
    noInterrupts();
        handleInput(Serial.read());
    interrupts();    
  }
}




static void handleInput (char c)
{
    if (c >= '0' && c <= '9')
      {
        value = 10 * value + c - '0';
        //Serial.println(value);
        return;
      }
    if (c >= 'a' && c <= 'z') {
//        Serial.print(value);
//        Serial.println(c);
    }

    if (c > ' ')
      {
        switch (c)
          {
            case 'm': 
              dimming = value;
              dimtime = (100*dimming);
              Serial.println("Updated variables: dimming, dimtime");
              printVariables();
              break;
            case 's': 
              openshift = value;
              Serial.println("Updated variables: openshift");
              printVariables();
              break;
            case 'd': 
              opendelay = value;
              Serial.println("Updated variables: opendelay");
              printVariables();
              break;
            default:
              Serial.println("Command don't understud!");
              Serial.println();
          }
      }
    value = 0;
}
