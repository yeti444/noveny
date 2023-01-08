#include "thingProperties.h"
#include "arduino_secrets"

int Relaypin = 2;
int sensorPin = A0;

int sensorValue;
int soilMoistureValue;
int soilMoisturePercent;

const int DryValue = 1000;  // a setupCode-ban látható módon szereztük meg
const int WetValue = 400;   // ugyan így
int pump_trigger = 30;
String pump_status_text = "OFF";


int periodShort = 1500;  // 1,5 másodperc
int periodLong = 10000;  // 10 másodperc
int periodUpdate = 5000;  // 5 másodperc
unsigned long time_now = 0;
unsigned long time_nowUpdate = 0;

void setup() {
  Serial.begin(9600);
  delay(1500);

  initProperties();


  ArduinoCloud.begin(ArduinoIoTPreferredConnection, false);  // Az arduino cloud szolgáltatását vettük ígénybe

  pinMode(Relaypin, OUTPUT);
  digitalWrite(Relaypin, LOW);
  pump_Status = false;

  pinMode(sensorPin, INPUT);

  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();
}

void loop() {
  
  moist();
  
  if (soilMoisturePercent <= pump_trigger) {
  pumpOn();
  time_now = millis();

  while(millis() < time_now + periodShort)
  {
    moist();
    delay(1000);
    if(millis() >= time_nowUpdate + periodUpdate)
    {
        time_nowUpdate += periodUpdate;
        ArduinoCloud.update();
    }
  }
  
  
  
  pumpOff();
  time_now = millis();
  
  while(millis() < time_now + periodLong)
  {
    moist();
    delay(1000);
    if(millis() >= time_nowUpdate + periodUpdate)
    {
        time_nowUpdate += periodUpdate;
        ArduinoCloud.update();
    }
  }
  
  }
  else
  {
    delay(1000);
  }
  
  
  if(millis() >= time_nowUpdate + periodUpdate){
        time_nowUpdate += periodUpdate;
        ArduinoCloud.update();
  }
  
  
}

void pumpOn() {
  digitalWrite(Relaypin, HIGH);
  pump_status_text = "ON";
  pump_Status = true;
  moist();
  ArduinoCloud.update();
  
}

void pumpOff() {
  digitalWrite(Relaypin, LOW);
  pump_status_text = "OFF";
  pump_Status = false;
  moist();
  ArduinoCloud.update();
}

void moist() {
  soilMoistureValue = analogRead(sensorPin);
  soilMoisturePercent = map(soilMoistureValue, DryValue, WetValue, 0, 100);  // "map-oljuk" a %-ra
  soilMoisturePercent = constrain(soilMoisturePercent, 0, 100);              // hibakezelés 0-nál alacsonyabb illteve 100-nál magasabb % érték kiküszöbölése
  current_Moisture = soilMoisturePercent;
  Serial.println(soilMoistureValue);
}
void onTriggerLevelChange() {
  pump_trigger = trigger_Level;
}
