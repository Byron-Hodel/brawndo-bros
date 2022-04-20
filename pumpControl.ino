#include "Adafruit_seesaw.h"

class PumpControl{

private:
     
int pumpState = LOW;             // pumpState used to set the pump
int pumpPin = 2;

unsigned long previousMillis = 0;       
unsigned long lastQuench = 0;           // stores last time pump was set off
unsigned long lastDrink = 0;            // stores last time pump was set on
unsigned long previousPoll = 0;
unsigned long pollRate = 1000;
unsigned long pumpLastRun = 0;

long OnTime = 1;           // milliseconds of on-time
long OffTime = 10000;          // milliseconds of off-time *!* RESET TO 300000?

unsigned long moistureLimit = 450;

bool hasPumpRan = false;

String outLine;
String comma = ", ";
Adafruit_seesaw ss;




public:

PumpControl(){} 

~PumpControl(){}

void begin()
{
    if (!this->ss.begin(0x36)) 
    {
        //Serial.println("ERROR! Plant still craves this...");
        while(1) delay(1);
    } 
    else 
    {
        //Serial.print("THIRST MUTILATION COMMENCING!");
        //Serial.println(ss.getVersion(), HEX);
    }
}

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

bool isThirsty(unsigned long currentMillis)
{
    if((this->getMoist() < moistureLimit) && (pumpState == LOW) && (currentMillis - previousMillis >= OffTime))
    {
        //Serial.println("IS THIRSTY"); //*!* remove from final
        return true;
    }
    return false;
    //Serial.println("*!* ERROR *!*!"); //*!*remove from final
}// END isThirsty()

void quench(unsigned long currentMillis)
{
    //Serial.println("quench"); //*!* remove from final
    
    pumpState = HIGH;  // turn it on
    previousMillis = currentMillis;   // Remember the time
    digitalWrite(pumpPin, pumpState);    // Update the actual pump
    hasPumpRan = true;
}// END quench

bool notThirsty(unsigned long currentMillis)
{
    if((this->getMoist() > moistureLimit) && (pumpState == HIGH) && (currentMillis - previousMillis >= OnTime))
    {
        //Serial.println("Not Thirsty"); //*!* remove from final
        return true;
    }
    return false;
}//END notThirsty()

void quenched(unsigned long currentMillis)
{
    //Serial.println("quenched"); //*!* remove from final
    
    pumpState = LOW;  // Turn it off
    previousMillis = currentMillis;  // Remember the time
    digitalWrite(pumpPin, pumpState);  // Update the actual pump
}// END quenched

bool inStasis(unsigned long currentMillis)
{
    //Serial.println("inStasis"); //*!* remove from final
    if (hasPumpRan == false)
    {
      pumpLastRun = 0;
    } 
    else
    {
      pumpLastRun = currentMillis / 1000;
    }

    if(currentMillis - previousPoll >= pollRate)
    {
        //Serial.println("0 *!*");
        return true;
    }
    else
    {
        //Serial.println("1 *!*");
        return false;
    }
}// end inStasis()

void logStatus(unsigned long currentMillis)
{   
    outLine = pumpLastRun + comma + this->getMoist() + comma + this->getTempC();
    Serial.println(outLine);
    previousPoll = currentMillis;
}

/**************************************/

void printMillis(unsigned long currentMillis)
{
  Serial.println(currentMillis + comma +  "prev:: " + previousMillis + comma + "span:: " + (currentMillis - previousMillis)
   + comma + "On:: " + OnTime + comma + "Off:: " + OffTime + comma + "Pump:: " + pumpLastRun);

  //*!* remove from final: if(hasPumpRan) Serial.println("YES"); 
  //*!* remove from final: else Serial.println("NO"); 
}

};//END class pumpControl

/*******************************************/

PumpControl pc;
int pumpPin = 2;

void setup() 
{
  Serial.begin(9600);
  pc.begin();
  pinMode(pumpPin, OUTPUT);
}//END setup()

void loop() {

  unsigned long currentMillis = millis();
  //float tempC = pc.getTempC();            
  uint16_t capread = pc.getMoist();       

  //pc.printMillis(currentMillis); //*!*
  if(pc.inStasis(currentMillis))  
  {
    //Serial.println("A *!*");
    pc.logStatus(currentMillis);
  }
  if (pc.notThirsty(currentMillis))
  {
    //Serial.println("B *!*");
    pc.quenched(currentMillis);
  }
  else if (pc.isThirsty(currentMillis))
  {
    //Serial.println("C *!*");
    pc.quench(currentMillis);
  }
  

  //pc.printMillis(currentMillis); //*!*
  //delay(2000);   //*!* remove from final
}//END loop()
