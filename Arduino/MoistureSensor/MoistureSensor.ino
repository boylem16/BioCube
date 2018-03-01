void setup() {
  Serial.begin(9600);
}
void loop() {
  float sensorValue = analogRead(A2);
  float voltage = -(((sensorValue - 520) / 2)-100);
  Serial.println(voltage);
  delay(500);
}
