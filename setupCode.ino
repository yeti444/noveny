//test -- hogy megtudjuk a dry (minimumm) és wet (maximum) értéket a szenzorunknál

//int Relaypin= 2;
int sensorPin = A0; 
int sensorValue;  

int soilMoistureValue;

void setup() {
  Serial.begin(9600);
  
  pinMode(Relaypin, OUTPUT);
  digitalWrite(Relaypin, LOW);
}

void loop() {
  soilMoistureValue = analogRead(sensorPin);
  Serial.println(soilMoistureValue);
  delay(100);
}
