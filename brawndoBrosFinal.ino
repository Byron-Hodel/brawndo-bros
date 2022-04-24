#include <Arduino.h>
#include "Adafruit_seesaw.h"
#include <LiquidCrystal.h>



class PumpControl{
private:

const unsigned long HOUR = 3600000;

int pumpState = LOW;             // pumpState used to set the pump
int pumpPin = 2;
int pumpEventCount = 0;

unsigned long previousMillis = 0;       
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
        while(1) delay(1);
    } 

    systemState = "Online";
}//END begin

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

int getMoistPer()
{
    return moistPer;
}//END getMoist

int getSysFault()
{
  return systemFault;
}//END getSysFault

bool isThirsty(unsigned long currentMillis)
{
    if((moistPer < moistureLimit) && (pumpState == LOW) && (currentMillis - previousMillis >= OffTime))
    {
        return true;
    }
    return false;
}// END isThirsty()

void quench(unsigned long currentMillis)
{    
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
        return true;
    }
    return false;
}//END notThirsty()

void quenched(unsigned long currentMillis)
{   
    pumpState = LOW;  // Turn it off
    previousMillis = currentMillis;  // Remember the time
    digitalWrite(pumpPin, pumpState);  // Update the actual pump
}// END quenched

bool inStasis(unsigned long currentMillis)
{
    if (hasPumpRan == false)
    {
      pumpLastRun = 0;
    } 
    else if (pumpState == LOW)
    {
      pumpLastRun = (currentMillis - previousMillis) / 60000;
    }

    if(currentMillis - previousPoll >= pollRate)
    {
        return true;
    }
    else
    {
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

    outLine = pumpLastRun + comma + this->moistPer + comma + this->getTempC() + comma + pumpState;
    Serial.println(outLine);
    previousPoll = currentMillis;
    //countEvents(currentMillis);
}

void countEvents(unsigned long currentMillis)
{
  switch (pumpEventCount)
  {
    case 1: 
      if(eventStamp[0] == 0)  
        eventStamp[0] = currentMillis;

      break;
    case 2:
      if(eventStamp[1] == 0)  
        eventStamp[1] = currentMillis;

      break;
    case 3:
      if(eventStamp[2] == 0)  
        eventStamp[2] = currentMillis;

      break;
    case 4:
      if(eventStamp[3] == 0)  
        eventStamp[3] = currentMillis;
      
      break;
    case 5:
      if(eventStamp[4] == 0)  
        eventStamp[4] = currentMillis;


      if((eventStamp[4] - eventStamp[0]) < HOUR)  /*&& currentMillis > HOUR*/
      {
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
  eventStamp[0] = eventStamp[1];
  eventStamp[1] = eventStamp[2];
  eventStamp[2] = eventStamp[3];
  eventStamp[3] = eventStamp[4];
  eventStamp[4] = 0;
  pumpEventCount--;
}//END reorderStamps

void display(LiquidCrystal &lcd, int x)
{
  String record_display = (String)("T:" + (String)this->getTempC() + " " + "M:" + (int)this->getMoistPer() + "  ");
  switch(x)
  {
 
    case 1:
      lcd.setCursor(0, 1);
      lcd.print(record_display);

    break;
    case 2:
      lcd.setCursor(0,0);
      lcd.print("THIRST MUTILATED");
      lcd.setCursor(0, 1);
      lcd.print(record_display);

    break;
    case 3:
      lcd.setCursor(0,0);
      lcd.print("QUENCHING THIRST");
      lcd.setCursor(0, 1);
      lcd.print(record_display);
      
      break;
    case 4:
      lcd.setCursor(0,0);
      lcd.print("A Fault Occured ");
      lcd.setCursor(0,1);
      lcd.print("fix and reset   ");

      break;
  }//END switch
}//END display()

};

PumpControl pc;
int pumpPin = 2;

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);


void setup() 
{
  Serial.begin(9600);
  lcd.begin(16, 2);

  lcd.print("BRAWNDO!!!");
  pc.begin();
  pinMode(pumpPin, OUTPUT);

  //Serial.println("MinsSinceLastPumpEvent,Moisture,SoilTempC,PumpState"); //header for pi
}//END setup()

void loop() {

  unsigned long currentMillis = millis();

  if(pc.inStasis(currentMillis))  
  {
    pc.logStatus(currentMillis);
    pc.display(lcd, 1);
  }
  if (pc.notThirsty(currentMillis))
  {
    pc.quenched(currentMillis);
    pc.display(lcd, 2);
  }
  else if (pc.isThirsty(currentMillis))
  {
    pc.quench(currentMillis);
    pc.display(lcd, 3);
  }

/*!* 
  while(pc.getSysFault() == true)
  {
    pc.display(lcd, 4);
  }
/*!*/
  
}//END loop()




/*
board :: 
pin2 -> j21
10k resistor :: f21 -> j27
led :: f27 -> f33
wire ::i33 -> common GND
wire :: common GND -> board GND

2 -> resistor -> led -> wire to common GND ->
**********
sensor ::
Green -> SCL
White -> SDL
Red -> 5v
Green -> board GND
*/
