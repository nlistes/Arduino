#include <DHT.h>
#include <JeeLib.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define SERIAL  0   // set to 1 to also report readings on the serial port
#define RADIO   1   

#define DHT22_PIN 8
#define ONE_WIRE_BUS 6
#define photocellPower 7

int powerPin=A0;
int photocellPin=A1;

#define DHTTYPE         DHT22   // DHT 22  (AM2302)
#define MEASURE_PERIOD  15 // how often to measure, in seconds

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

TsendDataV1 sendData;

DHT dht22(DHT22_PIN, DHTTYPE, 3);
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

// Other variables used in various places in the code:
static byte nodeID;       // node ID used for this unit
bool dataReady = false;
long timeCounter = 0;

// devēju tekošā un iepriekšējā nolasītā vērtība
float H, pH; // mitrums
float T1, pT1, T2, pT2; // temperatūra

static void serialFlush()
{
    #if ARDUINO >= 100
        Serial.flush();
    #endif  
    delay(2); // make sure tx buf is empty before going back to sleep
}

ISR(WDT_vect) { Sleepy::watchdogEvent(); }

void setup(void)
{
    cli();
    CLKPR = bit(CLKPCE);
    //CLKPR = 1; // div 2, i.e. slow down to 8 MHz
    sei();
#if SERIAL
        Serial.begin(9600);
        Serial.print("[envMonitor]");
        nodeID = rf12_config();
        serialFlush();
#else
        nodeID = rf12_config(0); // don't report info on the serial port
#endif
  dht22.begin();
  sensors.begin();
  pinMode(photocellPower, OUTPUT);
  digitalWrite(photocellPower, LOW);
}


void loop(void)
{ 
  #if !RADIO
    if ((millis() - timeCounter) > MEASURE_PERIOD * 1000)
  #endif
  {
  timeCounter = millis();
  
  T1 = dht22.readTemperature();
  //if ((T > (pT + 0.2)) || (T < (pT - 0.2))) pT = T; else T = pT;
  sendData.data.T1 = (int)(T1 * 10);
  
  sensors.requestTemperatures();
  T2 = sensors.getTempCByIndex(0);
  //if ((T > (pT + 0.2)) || (T < (pT - 0.2))) pT = T; else T = pT;
  sendData.data.T2 = (int)(T2 * 10);
  
  H = dht22.readHumidity();
  //if ((H > (pH + 0.4)) || (H < (pH - 0.4))) pH = H; else H = pH;
  sendData.data.H = (int)(H * 10);  // pārvēršam par veselu skaitli ievērojot vienu zīmi aiz komata
  
  digitalWrite(photocellPower, HIGH);
  sendData.data.L = analogRead(photocellPin);  
  delay(2);
  sendData.data.L = analogRead(photocellPin);  
  digitalWrite(photocellPower, LOW);
  
  sendData.data.P = analogRead(powerPin);
  delay(2);
  sendData.data.P = analogRead(powerPin);
  
  sendData.data.M = 0;
  sendData.data.X = nodeID;
  dataReady = true;

#if SERIAL
  Serial.println("DATA BEGIN");
  Serial.print("T1="); 
  Serial.println(sendData.data.T1);
  Serial.print("T2="); 
  Serial.println(sendData.data.T2);
  Serial.print("H="); 
  Serial.println(sendData.data.H);
  Serial.print("L=");
  Serial.println(sendData.data.L);    
  Serial.print("P=");
  Serial.println(sendData.data.P);
  Serial.print("M=");
  Serial.println(sendData.data.M);
  Serial.print("X=");
  Serial.println(sendData.data.X);
  Serial.println("DATA END");
  serialFlush();
#endif
  };

if (dataReady)
  {
#if RADIO    
    while (!rf12_canSend())
      rf12_recvDone();
      rf12_sendStart(0, sendData.buf, 14);
      dataReady = false;
    rf12_sendWait(2);
    rf12_sleep(RF12_SLEEP);
    Sleepy::loseSomeTime(MEASURE_PERIOD * 1000);
    rf12_sleep(RF12_WAKEUP);
#endif
  };  

}

