#include "Adafruit_seesaw.h"

class PumpControl{

private:

const unsigned long HOUR = 3600000;
const unsigned long MIN = 60000;

int pumpState = LOW;             // pumpState used to set the pump
int pumpPin = 2;
int pumpEventCount = 0;

unsigned long previousMillis = 0;       
unsigned long lastQuench = 0;           // stores last time pump was set off
unsigned long lastDrink = 0;            // stores last time pump was set on
unsigned long previousPoll = 0;
unsigned long pollRate = 1000;
unsigned long pumpLastRun = 0;

unsigned long eventStamp[5];      //holds time stamps for 5 events

long OnTime = 10000;           // milliseconds of on-time
long OffTime = 3000;          // milliseconds of off-time *!* RESET TO 300000

unsigned long moistureLimit = 60;
int moistPer = 0;

bool hasPumpRan = false;
bool systemFault = false;

String outLine;
String comma = ",";
String systemState = "offline";
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
    systemState = "Online";
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
    if((moistPer < moistureLimit) && (pumpState == LOW) && (currentMillis - previousMillis >= OffTime))
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
    pumpLastRun = 0;
    pumpEventCount++;
}// END quench

bool notThirsty(unsigned long currentMillis)
{
    if((pumpState == HIGH) && (currentMillis - previousMillis >= OnTime))
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
    else if (pumpState == LOW)
    {
      pumpLastRun = (currentMillis - previousMillis) / 1000;
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
    if(this->getMoist() < 350){
      moistPer = 0;}
    else if (this->getMoist() >= 1000){
      moistPer = 100;} 
    else{
      moistPer = (this->getMoist() - 350) / 6.5;}

    outLine = pumpLastRun + comma + moistPer + comma + this->getTempC() + comma + pumpState;
    Serial.println(outLine);
    previousPoll = currentMillis;
    countEvents(currentMillis);
}

void countEvents(unsigned long currentMillis)
{
  switch (pumpEventCount)
  {
    case 1: 
      if(eventStamp[0] == 0)  
        eventStamp[0] = currentMillis;
      //Serial.print(eventStamp[0]);
      //Serial.println("*!***1");
      break;
    case 2:
      if(eventStamp[1] == 0)  
        eventStamp[1] = currentMillis;
      //Serial.print(eventStamp[1]); 
      //Serial.println("*!***2");
      break;
    case 3:
      if(eventStamp[2] == 0)  
        eventStamp[2] = currentMillis;
      //Serial.print(eventStamp[2]);
      //Serial.println("*!***3"); 
      break;
    case 4:
      if(eventStamp[3] == 0)  
        eventStamp[3] = currentMillis;
      //Serial.print(eventStamp[3]);
      //Serial.println("*!***4"); 
      break;
    case 5:
      if(eventStamp[4] == 0)  
        eventStamp[4] = currentMillis;
      //Serial.print(eventStamp[4]);
      //Serial.println("*!***5"); 

      /*Serial.println(eventStamp[0] + comma + eventStamp[1] + comma + 
                     eventStamp[2] + comma + eventStamp[3] + comma + 
                     eventStamp[4] + comma + (eventStamp[4] - eventStamp[0]));*/

      if((eventStamp[4] - eventStamp[0]) < HOUR)
      {
        //*!*Serial.println("fault");//*!*throw fault
        systemFault = true;
      }
      else
      {
        systemFault = false;
      }
      this->reorderStamps();
      break;
    default: break;
  }//END switch
}//END countEvents

void reorderStamps()

{
  //Serial.println("*!***REORDER");
  eventStamp[0] = eventStamp[1];
  eventStamp[1] = eventStamp[2];
  eventStamp[2] = eventStamp[3];
  eventStamp[3] = eventStamp[4];
  eventStamp[4] = 0;
  pumpEventCount--;
}

/**************************************

void printMillis(unsigned long currentMillis)
{
  Serial.println(currentMillis + comma +  "prev:: " + previousMillis + comma + "span:: " + (currentMillis - previousMillis)
   + comma + "On:: " + OnTime + comma + "Off:: " + OffTime + comma + "Pump:: " + pumpLastRun);

  //*!* remove from final: if(hasPumpRan) Serial.println("YES"); 
  //*!* remove from final: else Serial.println("NO"); 
} 
**************************************/

};//END class pumpControl

/*******************************************/

PumpControl pc;
int pumpPin = 2;

void setup() 
{
  Serial.begin(9600);
  pc.begin();
  pinMode(pumpPin, OUTPUT);

  Serial.println("MinsSinceLastPumpEvent,Moisture,SoilTempC,PumpState"); //header for pi
}//END setup()

void loop() {

  unsigned long currentMillis = millis();
  //float tempC = pc.getTempC();            
  //uint16_t capread = pc.getMoist();       

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




/*
board :: pin2 -> j21
10k resistor :: f21 -> j27
led :: f27 -> f33
wire ::i33 -> common GND
wire :: common GND -> board GND
**********
sensor ::
Green -> SCL
White -> SDL
Red -> 5v
Green -> board GND
*/


/*
To Do
if 5 pumpEvents in an hour throw system into fault

1hr in milisec = 3,600,000

everytime pump turns on, increment pumpCount






*/
