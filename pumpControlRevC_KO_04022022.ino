#include "Adafruit_seesaw.h"
int pumpPin =  2;      // the number of the pump pin
int pumpState = LOW;             // pumpState used to set the pump
unsigned long previousMillis = 0;        // will store last time pump ran
unsigned long previousPoll = 0;
unsigned long pollRate = 1000;
long OnTime = 10000;           // milliseconds of on-time
long OffTime = 300000;          // milliseconds of off-time
long moistureLimit = 450;
String outLine;
String comma = ",";


Adafruit_seesaw ss;

void setup() {
  Serial.begin(9600);
  
  if (!ss.begin(0x36)) {
//    Serial.println("ERROR! seesaw not found");
    while(1) delay(1);
  } else {
//    Serial.print("seesaw started! version: ");
//    Serial.println(ss.getVersion(), HEX);
  }

  pinMode(pumpPin, OUTPUT);
}

void loop() {

  unsigned long currentMillis = millis();
  float tempC = ss.getTemp();
  uint16_t capread = ss.touchRead(0);

  if(currentMillis - previousPoll >= pollRate)
  {
    outLine = (previousMillis / 1000) + comma + capread + comma + tempC;
    Serial.println(outLine);
    previousPoll = currentMillis;
  }
  
    if((capread > moistureLimit) && (pumpState == HIGH) && (currentMillis - previousMillis >= OnTime))
  {
    pumpState = LOW;  // Turn it off
    previousMillis = currentMillis;  // Remember the time
    digitalWrite(pumpPin, pumpState);  // Update the actual pump
  }
  else if ((capread < moistureLimit) && (pumpState == LOW) && (currentMillis - previousMillis >= OffTime))
  {
    pumpState = HIGH;  // turn it on
    previousMillis = currentMillis;   // Remember the time
    digitalWrite(pumpPin, pumpState);    // Update the actual pump
  }

}
