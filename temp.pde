// Example use of LCD3Wire library
// Almost a carbon-copy of LCD4BitExample.pde

#include <LCD3Wire.h>
#include <OneWire.h>
#include <DallasTemperature.h>


// Arduino pins
#define LCD_LINES 2  // number of lines in your display
#define DOUT_PIN  7  // Dout pin
#define STR_PIN   6  // Strobe pin
#define CLK_PIN   5  // Clock pin

#define LED_PIN   13 // we'll use the debug LED to output a heartbeat

#define ONE_WIRE_BUS 8
#define TEMPERATURE_PRECISION 9

LCD3Wire lcd = LCD3Wire(LCD_LINES, DOUT_PIN, STR_PIN, CLK_PIN); 

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
uint8_t insideThermometer[8], outsideThermometer[8];

typedef struct {
    float insideTemp;
    float outsideTemp;
} TData;

union
{
byte data[8];
TData Data;
} sendData;

void setup() { 
  Serial.begin(9600);
  lcd.init();
  pinMode(LED_PIN, OUTPUT);
  sensors.begin();
  sensors.getAddress(insideThermometer, 0);
  sensors.getAddress(outsideThermometer, 1);
  sensors.setResolution(insideThermometer, TEMPERATURE_PRECISION);
  sensors.setResolution(outsideThermometer, TEMPERATURE_PRECISION);
}

void loop() {  
  digitalWrite(LED_PIN, HIGH);  //light the debug LED
  sensors.requestTemperatures();
  sendData.Data.insideTemp = sensors.getTempC(insideThermometer);
  sendData.Data.outsideTemp = sensors.getTempC(outsideThermometer);
  digitalWrite(LED_PIN, LOW);
  //lcd.clear();
  lcd.cursorTo(1, 0);  //line=2, x=0.
  lcd.print(sendData.Data.insideTemp);
  lcd.cursorTo(2, 0);  //line=2, x=0.
  lcd.print(sendData.Data.outsideTemp);
  for (int i = 0;7;i++){
  Serial.write(sendData.data[i]);};
  delay(4000);
}
