/*
  The circuit:
 * LCD RS pin to digital pin 12 (A0)
 * LCD EN pin to digital pin 11 (A1)
 * LCD D4 pin to digital pin 5  (A2)
 * LCD D5 pin to digital pin 4  (A3)
 * LCD D6 pin to digital pin 3  (A4)
 * LCD D7 pin to digital pin 2  (A5)
 * LCD R/W pin to ground
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)
 */

#include <Keypad.h>
#include <LiquidCrystal.h>

const byte ROWS = 4; //four rows
const byte COLS = 4; //three columns
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte colPins[COLS] = {9, 10, 11, 12}; //connect to the column pinouts of the keypad
byte rowPins[ROWS] = {8, 7, 6, 5}; //connect to the row pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );


LiquidCrystal lcd(A0, A1, A2, A3, A4, A5);

#define btnAPin 2
#define btnBPin 3
#define spkrPin 4
#define ledAPin 15
#define ledBPin 14

int btnAState;             // the current reading from the input pin
int btnAStateLast = LOW;   // the previous reading from the input pin

int btnReading;

long lastDebounceTime = 0;  // the last time the output pin was toggled
long debounceDelay = 50;    // the debounce time; increase if the output flickers

int ledAState;
int ledAStateLast = LOW;

void setup()
{
  Serial.begin(9600);
  pinMode(btnAPin, INPUT);
  pinMode(btnBPin, INPUT);
  pinMode(spkrPin, OUTPUT);
  pinMode(ledAPin, OUTPUT);
  pinMode(ledBPin, OUTPUT);
  ledAState = ledAStateLast;
  digitalWrite(ledAPin, ledAState);
  lcd.begin(20, 4);
  lcd.print("Hello world!!!  ");
}

void loop()
{
  btnReading = digitalRead(btnAPin);
  if (btnReading != btnAStateLast)                     // If the switch changed, due to noise or pressing:
    lastDebounceTime = millis();                      // reset the debouncing timer
  if ((millis() - lastDebounceTime) > debounceDelay)  // whatever the reading is at, it's been there for longer
    btnAState = btnReading;      // than the debounce delay, so take it as the actual current state:

  if ((btnAState == HIGH) && (btnAState != btnAStateLast)) 
   {
     ledAState = !ledAState;
     digitalWrite(ledAPin, ledAState);
   }
  btnAStateLast = btnReading;

  char key = keypad.getKey();
  if (key != NO_KEY)
  {
    digitalWrite(spkrPin, HIGH);
    delay(10);
    digitalWrite(spkrPin, LOW);
    switch (key)
    {
      case 'A':
        lcd.setCursor(0, 0);
        lcd.print("Hello world!!!  ");
        Serial.println("Hello world!!!  ");
        break;
      case 'B':
        lcd.setCursor(0, 1);
        lcd.print("Welcome to LCD...");
        Serial.println("Welcome to LCD...");
        break;
      case 'D':
        lcd.clear();
        Serial.println();
        break;
      default:
        lcd.print(key);
        Serial.println(key);
    }
  }

}

