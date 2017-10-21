#include <Bounce.h>
#include <LiquidCrystal_SR_LCD3.h>
#include <UIPEthernet.h>
#include <PubSubClient.h>

byte MAC_ADDRESS[] = { 0x90, 0xA2, 0xDA, 0x0D, 0x31, 0xB8 };
#define MQTT_SERVER "10.20.30.60"

Bounce meterBounce = Bounce( A5, 20);

LiquidCrystal_SR_LCD3 lcd(A2, A0, A1);
EthernetClient ethClient;
PubSubClient mqttClient(ethClient);
char message_buff[30];
  
int meterCount = 0;
unsigned long meterTime, meterTimePrevious = 0;

float a, b;
unsigned long c;


void setup()
  {
    c = 0;
    Serial.begin(9600);
    pinMode(A5, INPUT);
    lcd.begin(16, 2);        // set up the LCD's number of columns and rows
    lcd.print("Getting IP...");
    lcd.setCursor(0,1);
    Ethernet.begin(MAC_ADDRESS);
    lcd.print(Ethernet.localIP());
    mqttClient.setServer(MQTT_SERVER, 1883);
    mqttClient.connect("flowCounter");
  }

void loop()
  {  
    if (meterBounce.update())
      if (meterBounce.risingEdge())
        {
          meterTime = millis();
          meterCount++;
           b = (3600000.0 / (meterTime - meterTimePrevious));
           c = b * 1000.0;
           lcd.clear();
           lcd.print("Count: "); 
           lcd.print(meterCount);
           lcd.setCursor(0,1);
           lcd.print("Flow: "); 
           lcd.print(c / 1000);
           lcd.print(".");
           lcd.print(c % 1000);
           lcd.print("  ");
           meterTimePrevious = meterTime;
           String pubString = String(meterCount);
           pubString.toCharArray(message_buff, pubString.length()+1);
           mqttClient.publish("H2O/Count",message_buff);
           
           //mqttClient.publish("H2O/Flow",b);
       Serial.print(" Litri: ");
       Serial.println(meterCount);
       Serial.print("Plusma: ");
       Serial.println(b);
       Serial.println(message_buff);
         } 
         mqttClient.loop();
  }



