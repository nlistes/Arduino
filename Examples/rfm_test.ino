#include <JeeLib.h>

char buffer[40] = "";
byte pos=0;
byte sendIt = 0;

void ledblink(unsigned int del) {
  digitalWrite(0, LOW);   // set the LED on
  delay(del);              // wait for a second
  digitalWrite(0, HIGH);    // set the LED off
  delay(del);              // wait for a second
}

char payload[] ="T..H..";

#include <dht.h>
dht DHT;
#define DHT11_PIN 9


ISR(WDT_vect) {
   Sleepy::watchdogEvent();
}

void setup() {
  
  ACSR |= (1<<ACD);
  ADCSRA &= ~(1<<ADEN);
  PRR |= (1<<PRADC);
  
  pinMode(0, OUTPUT); 
  
  rf12_initialize(2, RF12_868MHZ);
  delay(1000);
  ledblink(100);
  Sleepy::watchdogInterrupts(9);
}

void loop() {

  rf12_sleep(RF12_SLEEP);
  Sleepy::loseSomeTime(60000);
  rf12_sleep(RF12_WAKEUP);

  while (!rf12_canSend())
    rf12_recvDone();

  
  int chk = DHT.read11(DHT11_PIN);
  if (chk == 0) {
    payload[1] = (int)DHT.temperature/10+'0';
    payload[2] = (int)DHT.temperature%10+'0';
    payload[4] = (int)DHT.humidity/10+'0';
    payload[5] = (int)DHT.humidity%10+'0';
  }
  

  rf12_sendStart(0, &payload, sizeof payload);
  ledblink(10);  

  
  rf12_sendWait(3);
    
}
