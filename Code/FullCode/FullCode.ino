#define TEMPERATURE_PIN A1
#define RAIN_PIN A0
#define MOISTURE_PIN A2

String OnOff;   

void setup(){
  Serial.begin(9600);
}

/*
 * Pins occupied :
 *   Temp Sensor : A1,GND,5V;
 *   Rain Sensor : A0,GND,5V
 *   Bluetooth Module : 0(RX),1(TX),3.3V,GND
 *   Moisture Sensor : A2,GND,5V;
 *   Add Data for other sensors:
 *   
 */
void loop(){
  OnOff = "";//Resets string a 
  while (Serial.available()){ 
    delay(10); 
    char c = Serial.read(); 
    OnOff += c; 
  } 
  
  if(OnOff.equals("OFF")){
    while(!Serial.available()){
      Serial.println("|||");
      delay(1000);
    }
  }
  else if(OnOff.equals("ON")){
    while(!Serial.available()){
      printData();
      delay(1000); 
    }
  } 
}

void printData(void){
  // "|" is used as a delimeter
  Serial.println(String(getTemperature())+"|"+String(getHumidity())+"|"+String(isRaining())+"|"+String(getMoisture()));
}
//Returns temperature in C
int getTemperature(void){
  int temp = analogRead(TEMPERATURE_PIN);
  return temp * 0.48828125;   // convert output (mv) to readable celcius
}
//Returns humidity in %
int getHumidity(void){
  return 1;
}
//Returns current status of rain
String isRaining(void)
{
  int x = analogRead(RAIN_PIN);
  
  if(x<=1023 && x>=800)
    return "No rain";
  else if(x<=800 && x>=500)
    return "Light rain";
  else if(x<=500 && x>=300)
    return "Heavy rain";
  else
    return "Very heavy rain";
}
//Returns soil moisture in %
int getMoisture(void){
  int tmpMoisture = analogRead(MOISTURE_PIN);
  int moisture = map(tmpMoisture,550,0,0,100);
  return moisture;
}
