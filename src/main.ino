#include "arduino_secrets.h"
#include "thingProperties.h"

int Relaypin= 2;
int sensorPin = A0; 

int sensorValue;  
int soilMoistureValue;
int soilMoisturePercent;

const int DryValue = 1017; // a setupCode-ban látható módon szereztük meg 
const int WetValue = 350;  // ugyan így
int pump_trigger = 30;
String pump_status_text = "OFF";

void setup() {
  Serial.begin(9600);
  delay(1500); 

  initProperties();

  
  ArduinoCloud.begin(ArduinoIoTPreferredConnection); // Az arduino cloud szolgáltatását vettük ígénybe
  
  pinMode(Relaypin, OUTPUT);
  digitalWrite(Relaypin, LOW);
  pump_Status = false;
  
  pinMode(sensorPin, INPUT);
  
  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();
}

void loop() {
  ArduinoCloud.update();
  
  soilMoistureValue = analogRead(sensorPin);
  soilMoisturePercent = map(soilMoistureValue, DryValue, WetValue, 0, 100); // "map-oljuk" a %-ra
  soilMoisturePercent = constrain(soilMoisturePercent, 0, 100); // hibakezelés 0-nál alacsonyabb illteve 100-nál magasabb % érték kiküszöbölése

  current_Moisture = soilMoisturePercent;
  


  if (soilMoisturePercent <= pump_trigger) {
    pumpOn();
 
  } else {
    pumpOff();
  }
  

  delay(10000);
}

    void pumpOn() {
  digitalWrite(Relaypin, HIGH);
  pump_status_text = "ON";
  pump_Status = true;
 
  }
 
void pumpOff() {
  digitalWrite(Relaypin, LOW);
  pump_status_text = "OFF";
  pump_Status = false;
 
  }
  
void onTriggerLevelChange()  {
  pump_trigger = trigger_Level;
}
