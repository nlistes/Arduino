#include <JeeLib.h>

typedef struct
  {
    int count;
    long flow;
  } TH2O;

union
  {
    byte dataByByte[6];
    TH2O dataByTH2O;
  } sendData;

void setup()
  {
    Serial.begin(9600);
    rf12_config();
  }

void loop()
  {  
    if (rf12_recvDone())
       if (rf12_crc == 0)
          {
//            Serial.print("   T/R:");
            for (byte i = 0; i < rf12_len; ++i)
              {
                sendData.dataByByte[i] = rf12_data[i];
//                Serial.print(' ');
//                Serial.print(sendData.dataByByte[i], DEC);
              }
//            Serial.println();
//            Serial.print(" Litri: ");
//            Serial.println(sendData.dataByTH2O.count);
//            Serial.print("Plusma: ");
//            Serial.println(sendData.dataByTH2O.flow);
//            Serial.println();
              Serial.println("DATA BEGIN");
              Serial.print("N2C=");
              Serial.println(sendData.dataByTH2O.count);
              Serial.print("N1F=");
              Serial.println(sendData.dataByTH2O.flow);
              Serial.println("DATA END");
          }
  }

