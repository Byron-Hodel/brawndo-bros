#include "Adafruit_seesaw.h"

class PumpControl{

private:
     
int pumpState = LOW;             // pumpState used to set the pump
unsigned long previousMillis = 0;        // will store last time pump ran
unsigned long previousPoll = 0;
unsigned long pollRate = 1000;
long OnTime = 10000;           // milliseconds of on-time
long OffTime = 300000;          // milliseconds of off-time
long moistureLimit = 450;
String outLine;
//String comma = ",";
Adafruit_seesaw ss;



PumpControl()
{
  if (!ss.begin(0x36)) {
//    Serial.println("ERROR! seesaw not found");
    while(1) delay(1);
  } else {
//    Serial.print("seesaw started! version: ");
//    Serial.println(ss.getVersion(), HEX);
  }
} //END constructor

~PumpControl(){}


public:

float getTempC()
{
    float tempC = ss.getTemp();
    return tempC;
} //END getTempC

uint16_t getMoist()
{
    uint16_t capread = ss.touchRead(0);
    return capread;
}//END getMoist

//return true if thirsty
bool isThirsty(unsigned long currentMillis)
{
    if((this->getMoist() > moistureLimit) && (pumpState == HIGH) && (currentMillis - previousMillis >= OnTime))
    {
        return false;
    }

    else if((this->getMoist() < moistureLimit) && (pumpState == LOW) && (currentMillis - previousMillis >= OffTime))
    {
        return true;
    }

    return false;

}// END isThirsty()

bool inStasis(unsigned long currentMillis)
{
    if(currentMillis - previousPoll >= pollRate)
    {
        return true;
    }
    else
    {
        return false;
    }
}// end inStasis()

void quench(unsigned long currentMillis)
{
    pumpState = HIGH;  // turn it on
    previousMillis = currentMillis;   // Remember the time
    digitalWrite(pumpPin, pumpState);    // Update the actual pump
}// END quench

void quenched(unsigned long currentMillis)
{
    pumpState = LOW;  // Turn it off
    previousMillis = currentMillis;  // Remember the time
    digitalWrite(pumpPin, pumpState);  // Update the actual pump
}// END quenched

void logStatus(unsigned long currentMillis)
{
    outLine = (previousMillis / 1000) + '\,' + this->getMoist() + '\,' + this->getTempC();
    Serial.println(outLine);
    previousPoll = currentMillis;
}

};//END class pumpControl

int pumpPin =  2; // the number of the pump pin
PumpControl pc;

void setup() 
{
  Serial.begin(9600);  
  pinMode(pumpPin, OUTPUT);
}//END setup()

void loop() {

  unsigned long currentMillis = millis();
  //float tempC = pc.getTempC();            
  //uint16_t capread = pc.getMoist();       

  
  if(pc.inStasis(currentMillis))  
      pc.logStatus(currentMillis);

  if (!pc.isThirsty(currentMillis))
      pc.quenched(currentMillis);

  else if (pc.isThirsty(currentMillis))
    pc.quench(currentMillis);

}//END loop()