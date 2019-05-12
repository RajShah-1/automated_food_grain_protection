#define TEMPERATURE_PIN A1

String OnOff;   

void setup(){
  Serial.begin(9600);
}

/*
 * Pins occupied :
 *   Temp Sensor : A1,GND,5V;
 *   Bluetooth Module : 0(RX),1(TX),3.3V,GND
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
//Returns YES or NO
String isRaining(void){
  return "NO";
}
//Returns soil moisture in %
int getMoisture(void){
  return 2;
}
