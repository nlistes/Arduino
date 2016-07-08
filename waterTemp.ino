#include <LiquidCrystal_SR_LCD3.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 8
#define TEMPERATURE_PRECISION 12

LiquidCrystal_SR_LCD3 lcd(A2, A0, A1);

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
uint8_t waterThermometer[8];
float waterTemp;

void printAddress(DeviceAddress deviceAddress)
{
  for (uint8_t i = 0; i < 8; i++)
  {
    // zero pad the address if necessary
    if (deviceAddress[i] < 16) Serial.print("0");
    Serial.print(deviceAddress[i], HEX);
  }
}

void setup() { 
  Serial.begin(9600);
    lcd.begin(16, 2);        // set up the LCD's number of columns and rows
    lcd.print("Aiziet...");
  sensors.begin();
  sensors.getAddress(waterThermometer, 0);
   Serial.print("Sensor Address: ");
  printAddress(waterThermometer);
 Serial.println(); 
  sensors.setResolution(waterThermometer, TEMPERATURE_PRECISION);
  Serial.print("Sensor Resolution: ");
  Serial.println(sensors.getResolution(waterThermometer), DEC);
}

void loop() {  
  sensors.requestTemperatures();
  waterTemp = sensors.getTempC(waterThermometer);
  Serial.print("Temp C: ");
  Serial.println(waterTemp);
  lcd.clear();
  lcd.setCursor(0,0);  //line=2, x=0.
  lcd.print(waterTemp);
  delay(4000);
}

