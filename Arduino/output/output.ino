#include <stdlib.h>
#include <string.h>
#include <LiquidCrystal.h>
LiquidCrystal lcd(7,8,9,10,11,12);
String check;
String temp;
int i = 2;
void setup(){
 Serial.begin(9600);
 lcd.begin(16,2);
 lcd.setCursor(0,0);
 lcd.blink();
 pinMode(13,OUTPUT); 
}


void loop(){
    //Serial.flush();
    delay(500);
 while(1){
  //lcd.clear();
  check = String(Serial.readString());
  //if(check == "temperature"){
  lcd.print(check);
  lcd.setCursor(0,1);
  delay(50);
  temp = (Serial.readString());
  lcd.print(temp);
  delay(500);
  lcd.clear();
   //check = "none";
   digitalWrite(13,HIGH);
  //} 
 } 
  
  
  

}
