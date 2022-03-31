  int time1 = 0;
  int temp = 50;
  int moisture = 100;
  int lightI = 1000;
  String comma = ",";
  String outLine;

void setup() {
  Serial.begin(9600);
  Serial.println("time,temp,moisture,lightIntensity");
  
  
}

void loop() {


  for(int i = 0; i < 101; i++)
  {
    time1++;
    temp++;
//    moisture++;
//    lightI++;
//    outLine = time1 + comma + temp + comma + moisture + comma + lightI;
     outLine = time1 + comma + temp;
    
    Serial.println(outLine);
    delay(100); //delay time in ms
  }
  time1 = 0;
  temp = 50;
//  moisture = 100;
//  lightI = 1000; 
  
//  Serial.print("Temperature: "); Serial.print(tempC); Serial.println("*C");
//  Serial.print("Capacitive: "); Serial.println(capread);
//  delay(100);


}
