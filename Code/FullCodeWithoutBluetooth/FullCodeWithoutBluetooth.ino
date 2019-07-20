// Install DHT sensor library by Adafruit V1.3.4 & Adafruit Unified Sensor V1.0.3 
 
#include <DHT.h>
#include <DHT_U.h>

#define TEMPERATURE_PIN A1
#define RAIN_PIN A0
#define MOISTURE_PIN A2
#define DHTPIN 2

#define DHTTYPE DHT11

String OnOff;   
DHT dht(DHTPIN, DHTTYPE);

void setup(){
  Serial.begin(9600);
  dht.begin();
}

/*
 * Pins occupied :
 *   Temp Sensor : A1, GND, 5V;
 *   Rain Sensor : A0, GND, 5V
 *   Bluetooth Module : 0(RX), 1(TX), 3.3V, GND
 *   Moisture Sensor : A2, GND, 5V;
 *   Humidity Sensor : 2, GND, 3.3v
 */
void loop(){
  OnOff = "ON";//Resets string OnOff 
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
  float t = dht.readTemperature();
  return (int)(t+0.5);   // convert output (mv) to readable celcius
}
//Returns humidity in %
int getHumidity(void){
  float h = dht.readHumidity();
  if(isnan(h)){
    return -1; //Returns -1 if it fails to read the value
  }
  return (int)(h+0.5);
  
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
