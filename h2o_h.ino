#include <Bounce.h>
#include <LiquidCrystal_SR_LCD3.h>

//static byte mymac[] = { 0x74,0x69,0x69,0x2D,0x30,0x31 };

//#define meterPin 6    // Plūsmas mērītājs
//Bounce meterBounce = Bounce( meterPin, 1);

#define counterPin_1 3
#define counterPin_2 4
#define counterPin_3 5
Bounce counterBounce[3] = {Bounce(counterPin_1, 20), Bounce(counterPin_2, 20), Bounce(counterPin_3, 20)};

Bounce buttonBounce = Bounce(A5, 50);

LiquidCrystal_SR_LCD3 lcd(A2, A0, A1);

//boolean dataReady = false;

typedef
 struct
  {
	unsigned long count;
	unsigned long flow;
  } TH2O;

typedef
 union
  {
	byte dataByByte[8];
	TH2O dataByTH2O;
  } TsendData;

//int meterCount = 0;
//unsigned long timeMeter, timeMeterPrev = 0;
unsigned long timeCounter[3], timeCounterPrev[3] = {0, 0, 0};

volatile int i = 0, j = 0;
float a, b;

TsendData sendDataCounter[3];//, sendDataMeter;

//void showData(int val)
//  {
//    lcd.clear();
//    lcd.print(val);
//    lcd.print(": ");
//    lcd.print(i);
//  }

void showData(int val)
  {
	lcd.clear();
		   lcd.print(val);
		   lcd.print(": ");
		   lcd.print(sendDataCounter[val].dataByTH2O.flow / 1000);
		   lcd.print(".");
		   lcd.print(sendDataCounter[val].dataByTH2O.flow % 1000);
		   lcd.print("  ");
		   lcd.print(sendDataCounter[val].dataByTH2O.count);
		   lcd.setCursor(0,1);
		   lcd.print(val);
		   lcd.print(": ");
		   lcd.print(i);
		   lcd.print(": ");
		   lcd.print(j);

//           lcd.setCursor(0,1);
//           lcd.print("M: ");
//           lcd.print(sendDataMeter.dataByTH2O.flow / 1000);
//           lcd.print(".");
//           lcd.print(sendDataMeter.dataByTH2O.flow % 1000);
//           lcd.print("  ");
//           lcd.print(sendDataMeter.dataByTH2O.count);
  }


void printIp (const byte *buf)
  {
	for (byte i = 0; i < 4; ++i)
	  {
	lcd.print( buf[i], DEC );
	if (i < 3)
	  lcd.print('.');
	  }
  }



void setup()
  {
	Serial.begin(9600);
//    pinMode(meterPin, INPUT);
	pinMode(A5, INPUT);
	pinMode(counterPin_1, INPUT);
	pinMode(counterPin_2, INPUT);
	pinMode(counterPin_3, INPUT);
	lcd.begin(16, 2);        // set up the LCD's number of columns and rows
	lcd.print("Aiziet...");
	lcd.setCursor(0,1);
	//rf12_config();
	//sendDataMeter.dataByTH2O.flow = 0;
  }

void loop()
  {

//   if (counterBounce[i].update())
//      if (counterBounce[i].risingEdge())
//        {
//           timeCounter[i] = millis();
//           sendDataCounter[i].dataByTH2O.count++;
//           a = 3600000.0 / (timeCounter[i] - timeCounterPrev[i]);
//           sendDataCounter[i].dataByTH2O.flow = a * 1000.0;
//           timeCounterPrev[i] = timeCounter[i];
//           //if (i == j)
//           showData(i);
//           //dataReady = false; //true;
//
//
//         }
//    i = i+1;
//    if (i == 3) i = 0;

	if (buttonBounce.update())
	  if (buttonBounce.risingEdge())
		{
//           showData(j);
		   lcd.setCursor(0,1);
		   lcd.print("M: ");
		   lcd.print(j);
		   j=j+1;
		}
//    if (meterBounce.update())
//      if (meterBounce.risingEdge())
//        {
//          meterCount++;
//          if ((meterCount%480) == 0)
//          {
//           timeMeter = millis();
//           sendDataMeter.dataByTH2O.count++;
//           b = 60000.0 / (timeMeter - timeMeterPrev);
//           sendDataMeter.dataByTH2O.flow = b * 1000.0;
//           showData();
//           meterCount = 0;
//           timeMeterPrev = timeMeter;
//           //dataReady = false; //true;
//          }
//         }


//    if (rf12_recvDone())
//      { if (rf12_crc == 0)
//          {
//            Serial.print("OK");
//            Serial.print(' ');
//            Serial.println((int) rf12_hdr);
//          }
//      }
//    if (dataReady && rf12_canSend())
//     {
//       Serial.print("   T/R:");
//       for (byte i = 0; i < 6; ++i)
//         {
//           Serial.print(' ');
//           Serial.print(sendDataCounter.dataByByte[i], DEC);
//         }
//       Serial.println();
//       Serial.print(" Litri: ");
//       Serial.println(sendDataCounter.dataByTH2O.count);
//       Serial.print("Plusma: ");
//       Serial.println(sendDataCounter.dataByTH2O.flow);
//       Serial.println();
//       rf12_sendStart(RF12_HDR_ACK | RF12_HDR_DST | 26, sendDataCounter.dataByByte, 6);
//       dataReady = false;
//     }
  }

