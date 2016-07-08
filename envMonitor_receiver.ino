// ID - node ID
// 

#include <JeeLib.h>
#include <LiquidCrystal_SR_LCD3.h>

typedef struct
  {
    int16_t H; //huminidity
    int16_t T1; //temperature
    int16_t T2; //temperature
    int16_t L; //light
    int16_t P; //power
    int16_t M; //movement
    int16_t X; //node id    
  } TData;

typedef union
  {
    TData data;
    byte buf[14];
  } TsendDataV1; 

long TFS, prevTFS, DFF, A = 0;
TsendDataV1 sendData;
LiquidCrystal_SR_LCD3 lcd(A2, A0, A1);

void showData()
  {
    lcd.clear();
    lcd.print("A:");
    lcd.print(A);
    lcd.print("  ");
    lcd.print("B:");
    lcd.print(DFF);

           lcd.setCursor(0,1);
           lcd.print("C:"); 
           lcd.print((float)sendData.data.T1/10);
           lcd.print(" ");
           lcd.print("H:"); 
           lcd.print((float)sendData.data.H/10);
  }


void setup()
  {
    lcd.begin(16, 2);        // set up the LCD's number of columns and rows
    Serial.begin(9600);
    lcd.print("SERIAL READY...");
    rf12_config();
  }

void loop()
  {  
    if (rf12_recvDone())
       if (rf12_crc == 0)
          {
            for (byte i = 0; i < rf12_len; ++i)
              {
                sendData.buf[i] = rf12_data[i];
              }
            TFS = millis()/1000;
            DFF = TFS - prevTFS;
            prevTFS = TFS;
            A++;
            Serial.println("DATA BEGIN");

            Serial.print("C1="); 
            Serial.println((float)sendData.data.T1/10);

            Serial.print("C2="); 
            Serial.println((float)sendData.data.T2/10);

            Serial.print("H="); 
            Serial.println((float)sendData.data.H/10);
            
            Serial.print("L=");
            Serial.println(sendData.data.L);    

            Serial.print("P=");
            Serial.println(sendData.data.P);

            Serial.print("X=");
            Serial.println(rf12_hdr & B00011111);
            
//            Serial.print("A=");
//            Serial.println(A);
//            Serial.print("B=");
//            Serial.println(DFF);
            Serial.println("DATA END");
            //showData();
          }
  }

