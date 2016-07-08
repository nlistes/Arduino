/*
 * IRremote: IRrecvDemo - demonstrates receiving IR codes with IRrecv
 * An IR detector/demodulator must be connected to the input RECV_PIN.
 * Version 0.1 July, 2009
 * Copyright 2009 Ken Shirriff
 * http://arcfn.com
 */

#include <IRremote.h>

const
  int RECV_PIN = 11;

IRrecv irReceiver(RECV_PIN);

boolean codeReceived = false;

decode_results results;
int irCode, storedCode = 0;

void setup()
{
  Serial.begin(9600);
  irReceiver.enableIRIn(); // Start the receiver
}

void loop() {
  codeReceived = irReceiver.decode(&results);
  if (codeReceived)
  {
    irCode = results.value;
    irReceiver.resume(); // Receive the next value
  }
  if ((irCode == -1) && ((storedCode == 8415) || (storedCode == 24735))) irCode = storedCode;
  if (irCode == -1) return;
  if (codeReceived) Serial.println(irCode); 
  storedCode = irCode;
}
