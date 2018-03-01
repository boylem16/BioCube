#include <stdlib.h>
#include <string.h>
#include <Time.h>
#include <TimeLib.h>
#include <Wire.h>
#include <Adafruit_BMP085.h>
#include <LiquidCrystal.h>
LiquidCrystal lcd(7,8,9,10,11,12);
//create an object of adafruit to use sensors
Adafruit_BMP085 bmp;
int temp = 0;
int pressure = 0;
int moisture = 0;
String check;
 //check = 0;



void setup(){

  //Set listening frequency
  Serial.begin(9600);
  //setting up bmp library
  bmp.begin();
  lcd.begin(16,2);
  lcd.setCursor(0,0);
  lcd.blink();
  lcd.write("Ready");
}  

int findtemperature(String check){
  int temp;
  
   //read value from sensor - get info from pressure/temperature sensor
   temp = bmp.readTemperature() * 10;
   //lcdwrite(check, temp);
   
   return temp;
}
int findpressure(){
 int pressure;


 pressure=bmp.readPressure();
 return pressure; 
  
}

int findmoisture(){
  float sensorValue = analogRead(A2);
  float moisture = sensorValue;
  return moisture;
}


void loop(){

  while(1) // continously execute
  {
    //String check;
    check = String(Serial.readString());
    Serial.flush();

    // read command from pi - check for number from raspberry pi, get next sensor info
  //String check = String(Serial.readString());
   
    // temperature info block  
    if(check == "temperature"){ 
      temp = findtemperature(check);
      //Serial.write(temp, DEC); //Displays on the arduino screen
    lcd.clear();
    lcd.print("temperature: ");
    delay(5);
    lcd.setCursor(0,1);
    lcd.print(((((float) temp/10)* 9 / 5) + 32));
      Serial.flush();
      //send hex info - sends the hex version of the statement to the raspberyy pi
      Serial.println(temp); 
      Serial.flush();
      // check for execute - makes sure the code executes based off of the flashing of an led
      check = "0"; 
    }
    else if(check == "pressure"){
      
    pressure = findpressure();
    lcd.clear();
    lcd.print("Pressure: ");
    delay(5);
    lcd.setCursor(0,1);
    lcd.print(pressure);
       Serial.flush();
       Serial.println(pressure);
       Serial.flush();
       check = "0";     
    }
    
    else if(check == "moisture"){
 
       moisture = findmoisture();
       lcd.clear();
       lcd.print("Moisture: ");
       delay(5);
       lcd.setCursor(0,1);
       lcd.print(moisture);
       Serial.flush();
       Serial.println(moisture);
       Serial.flush();
       check = "0";     
    }
    
    else{
      //lcd.print("err");
      Serial.println("E");
    }

  }
}
