#include <Wire.h>
#include <Adafruit_BMP085.h>

Adafruit_BMP085 bmp;
float temp;
int Pressure;
void setup(){
Serial.begin(9600);
bmp.begin();
}
void loop(){
 temp=bmp.readTemperature();
 Pressure=bmp.readPressure();
 Serial.print(temp);
 Serial.println( "*C");
 Serial.print(Pressure);
 Serial.println( "Pa");
delay(500); 
  
  
  
}
