/*
//This class handles moisture, light and temperature monitoring and control

//pin assignments are subject to change

//PIN 0 -> Moisture sensor INPUT
//PIN 1 -> Light sensor INPUT
//Pin 2 -> Temperature sensor INPUT

//Pin 11 -> Temperature alert
//Pin 12 -> Light activation/alert
//Pin 13 -> Pump activation/alert

*********
*/
#include <Arduino.h>
#include "Adafruit_Sensor.h"
#include "Adafruit_AM2320.h"
#include "Adafruit_seesaw.h"

const int DEFAULT_TEMP_MIN = 0;
const int DEFAULT_MOIST_MIN = 500;
const int DEFAULT_LIGHT_MIN = 0;


int moistureSensor = 1; //pin number for moisture sensor MAY NOT NEED BECAUSE OF AM2320
int lightSensor = 2;    //pin number for light sensor
int tempSensor = 3;     //pin number for temperature sensor

int pumpPin = 8;      //pin number for pump
int lightPin = 12;     //pin number for light
int tempPin = 13;      //pin number for temperature (superfulous)

Adafruit_AM2320 am2320 = Adafruit_AM2320();
Adafruit_seesaw seesaw;


class brawndoBro
{

    private:
        uint16_t moistureLevel;  //stores data from moisture sensor
        int lightLevel;  // "  "  "  " light sensor
        int temperatureLevel;    // " " " " temperature sensor

        int minMoisture;  //lowest allowed moisture
        int minLight;  //lowest light
        int minTemperature;  //lowest temp
        

    public:
        bool checkMoist(){
            Serial.print("FAWKKKK");
            if (this->moistureLevel <= 500000){
                return true;
            }
            else{
                return false;
            }
            //determine if moisture level is low enough to run pump
            //returns TRUE if low
        }

        bool checkLight(){
            if (this->lightLevel <= this->minLight){
                return true;
            }
            else{
                return false;
            }
            // determine if light needs to be run
            //returns TRUE if low
        }

        bool checkTemp(){
            if (this->temperatureLevel <= this->minTemperature){
                return true;
            }
            else{
                return false;
            }
            // is temperature too low
            //returns TRUE if low
            //send alert or log if temperatureLevel < minTemperature
        }

        void runPump(){
            digitalWrite(pumpPin, HIGH);
            // turn on pump, called in main
        }

        void runLight(){
            digitalWrite(lightPin, HIGH);
            // turn on light, called in main
        }

        void sendAlert(){  //rename to log status'?
            // either switch statements to: send alerts to app OR switch statement to log status'
        }

        void minMoistSetter(int setMinimum = DEFAULT_MOIST_MIN){
            this->minMoisture = setMinimum;
        }

        void minLightSetter(int setMinimum = DEFAULT_LIGHT_MIN){
            this->minLight = setMinimum;
        }

        void minTempSetter(int setMinimum = DEFAULT_TEMP_MIN){
            this->minTemperature = setMinimum;
        }

        void moistureLevelGetter(){
            this->moistureLevel = seesaw.touchRead(0);//moisture sensor!*!*!*!*!
            
        }

        void lightLevelGetter(){
            this->lightLevel = 0;//light sensor!*!*!*!
        }

        void temperatureLevelGetter(){
            this->temperatureLevel = am2320.readTemperature();
        }

};

brawndoBro brawndo;


void setup()
{
    Serial.begin(115200);
    //pinMode(moistureSensor, INPUT); //INPUT_PULLUP???
    pinMode(lightSensor, INPUT);  //INPUT_PULLUP???
    pinMode(tempSensor, INPUT);  //INPUT_PULLUP???
    
    pinMode(pumpPin, OUTPUT);
    pinMode(lightPin, OUTPUT);
    pinMode(tempPin, OUTPUT);

}
void loop()
{
    //check_moisture
    //digitalWrite(pumpPin, HIGH);
    uint16_t seesawData = seesaw.touchRead(0);
    Serial.print("Moisture = " ); Serial.println(seesawData);
    //brawndo.moistureLevelGetter();
    //if(brawndo.checkMoist()){brawndo.runPump();}
    //if moisture is low RUN_PUMP

    //check light
    //if(brawndo.checkLight())
    //{
        //brawndo.runLight();
    //}

    //if light is low RUN_LIGHT

    //check temp
    //if(brawndo.checkTemp())
    //{
        //brawndo.sendAlert();
    //}
    //if temp is low SEND_TEMP_ALERT
    
}


/*
#include "Adafruit_seesaw.h"

Adafruit_seesaw ss;

void setup() {
  Serial.begin(115200);

  Serial.println("seesaw Soil Sensor example!");
  
  if (!ss.begin(0x36)) {
    Serial.println("ERROR! seesaw not found");
    while(1) delay(1);
  } else {
    Serial.print("seesaw started! version: ");
    Serial.println(ss.getVersion(), HEX);
  }
}

void loop() {
  float tempC = ss.getTemp();
  uint16_t capread = ss.touchRead(0);

  Serial.print("Temperature: "); Serial.print(tempC); Serial.println("*C");
  Serial.print("Capacitive: "); Serial.println(capread);
  delay(100);
}
*/