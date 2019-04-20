#define TEMPERATURE_PIN A1   
void setup() {
  Serial.begin(9600);     
}
void loop() {
  int temp = getTemperature();   // convert output (mv) to readable celcius
  Serial.print("Temperature: ");
  Serial.print(temp);
  Serial.println("C");
  delay(1000);  
}

int getTemperature(){
  int temp = analogRead(TEMPERATURE_PIN);
  return temp * 0.48828125;   // convert output (mv) to readable celcius
}
