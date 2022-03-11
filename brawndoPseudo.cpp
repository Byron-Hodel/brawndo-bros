//brawndo.h

/**********
This class handles moisture, light and temperature monitoring and control

pin assignments are subject to change

PIN 0 -> Moisture sensor INPUT
PIN 1 -> Light sensor INPUT
Pin 2 -> Temperature sensor INPUT

Pin 11 -> Temperature alert
Pin 12 -> Light activation/alert
Pin 13 -> Pump activation/alert

**********/

int moistureSensor = 1;
int lightSensor = 2;
int tempSensor = 3;

int pumpPin = 11;
int lightPin = 12;
int tempPin = 13;

class brawndoBro
{

    private:
        int moistLVL;  //stores data from moisture sensor
        int lightLVL;  // "  "  "  " light sensor
        int tempLVL;    // " " " " temperature sensor

        int min_moist;  //lowest allowed moisture
        int min_light;  //lowest light
        int min_temp;  //lowest temp
        

    public:
        bool checkMoist(){

            //determine if moisture level is low enough to run pump
            //returns TRUE if low
            //run pump if moistLVL < min_moist


        }

        bool checkLight(){
            // determine if light needs to be run
            //returns TRUE if low
            //run light if lightLVL < min_light
        }

        bool checkTemp(){
            // is temperature too low
            //returns TRUE if low
            //send alert or log ig tempLVL < min_temp
        }

        void runPump(){
            // turn on pump, called by checkMoist
        }

        void runLight(){
            // turn on light, called by checkLight
        }

        void sendAlert(){  //rename to log status'?
            // either switch statements to: send alerts to app OR switch statement to log status'
        }

};

brawndoBro brawndo;

void setup()
{

}
void loop()
{
    //check_moisture
    if(brawndo.checkMoist())
    {
        brawndo.runPump();
    }
    //if moisture is low RUN_PUMP

    //check light
    if(brawndo.checkLight())
    {
        brawndo.runLight();
    }

    //if light is low RUN_LIGHT

    //check temp
    if(brawndo.checkTemp())
    {
        brawndo.sendAlert();
    }
    //if temp is low SEND_TEMP_ALERT
    
}