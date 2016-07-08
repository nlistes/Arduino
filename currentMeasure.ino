#include <JeeLib.h>
//#include <Bounce.h>
#include <LiquidCrystal_SR_LCD3.h>

//#define counterPin 7  // H2O counter pin
//Bounce counterBounce = Bounce( counterPin, 50); 

LiquidCrystal_SR_LCD3 lcd(A2, A0, A1);

long timeHome, timeHomePrev = 0;

boolean dataReady = false;

typedef struct
  {
    int current;
    long wattage;
  } TCurrent;

union
  {
    byte dataByByte[6];
    TCurrent dataByTCurrent;
  } sendData;

void setup()
  {
    Serial.begin(9600);
    pinMode(A5, INPUT);
    lcd.begin(16, 2);        // set up the LCD's number of columns and rows
    lcd.print("Strava: ");
    lcd.setCursor(0,1);
    lcd.print(" Jauda: ");
    rf12_config();
  }

void loop()
  {  
    timeHome = millis();
      if (timeHome - timeHomePrev > 2000)
        {
           sendData.dataByTCurrent.current = analogRead(A5);
           if (sendData.dataByTCurrent.current < 512) sendData.dataByTCurrent.current = 1024 - sendData.dataByTCurrent.current;
           sendData.dataByTCurrent.current = sendData.dataByTCurrent.current - 512;
           sendData.dataByTCurrent.wattage = 0;
           lcd.clear();
           lcd.print("Strava: ");
           lcd.setCursor(8,0);
           lcd.print(sendData.dataByTCurrent.current);
           lcd.setCursor(0,1);
           lcd.print(" Jauda: ");
           lcd.setCursor(8,1);
           lcd.print(sendData.dataByTCurrent.wattage);
           timeHomePrev = timeHome;
           dataReady = true;
         } 

    if (rf12_recvDone())
      { if (rf12_crc == 0)
          {
            Serial.print("OK");
            Serial.print(' ');
            Serial.println((int) rf12_hdr);
          }
      }  
    if (dataReady && rf12_canSend())
     {
       Serial.print("   T/R:");
       for (byte i = 0; i < 6; ++i)
         {
           Serial.print(' ');
           Serial.print(sendData.dataByByte[i], DEC);
         }
       Serial.println(); 
       Serial.print("Strava: ");
       Serial.println(sendData.dataByTCurrent.current);
       Serial.print(" Jauda: ");
       Serial.println(sendData.dataByTCurrent.wattage);
       Serial.println();
       rf12_sendStart(RF12_HDR_ACK | RF12_HDR_DST | 26, sendData.dataByByte, 6);
       dataReady = false;
     }
  }

