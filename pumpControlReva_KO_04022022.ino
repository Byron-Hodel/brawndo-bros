#include "Adafruit_seesaw.h"
int pumpPin =  2;      // the number of the LED pin
int pumpState = LOW;             // ledState used to set the LED
unsigned long previousMillis = 0;        // will store last time LED was updated
long OnTime = 10000;           // milliseconds of on-time
long OffTime = 300000;          // milliseconds of off-time
long moistureLimit = 450;
String outLine;
String comma = ",";


Adafruit_seesaw ss;

void setup() {
  Serial.begin(115200);

  //Serial.println("BrawndoBros!");
  
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
  // check to see if it's time to change the state of the LED
  unsigned long currentMillis = millis();
  
  float tempC = ss.getTemp();
  uint16_t capread = ss.touchRead(0);

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
  
//  Serial.print("Temperature: "); Serial.print(tempC); Serial.println("*C");
//  Serial.print("Capacitive: "); Serial.println(capread);
  outLine = capread + comma + tempC;
  Serial.println(outLine);
  delay(100);
}
