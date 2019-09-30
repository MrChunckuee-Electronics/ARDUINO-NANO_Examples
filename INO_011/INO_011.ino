/*******************************************************************************
 *
 *        Mostrar datos del DS1302 en LCD16x2 
 *
 *******************************************************************************
 * FileName:        INO_011.ino
 * Processor:       ATmega328
 * Complier:        Arduino v1.8.3
 * Author:          Pedro Sánchez (MrChunckuee)
 * Blog:            http://mrchunckuee.blogspot.com/
 * Email:           mrchunckuee.psr@gmail.com
 * Description:     Ejemplo basico para mostrar datos leidos del DS1302 
 *                  en una LCD16x2.
 *******************************************************************************
 * Rev.         Date            Comment
 *   v0.0.0     29/09/2019      Creación del firmware
 ******************************************************************************/

#include <Wire.h> 
#include <DS1302.h>
#include <LiquidCrystal_I2C.h>

DS1302 rtc(2, 3, 4); // Init the DS1302
LiquidCrystal_I2C lcd(0x27,16,2);  //Dirección  0x27 y 16 columnas x 2 filas

// Variables will change:
const int pinLed =  13;
int ledState = LOW;             // ledState used to set the LED
long previousMillis = 0;        // will store last time LED was updated
long interval = 1000;           // interval at which to blink (milliseconds)

void setup(){
  pinMode(pinLed, OUTPUT);

  // Setup Serial connection
  Serial.begin(9600);
  
  // Set the clock to run-mode, and disable the write protection
  rtc.halt(false);
  rtc.writeProtect(false);
  // The following lines can be commented out to use the values already stored in the DS1302
  rtc.setDOW(SUNDAY);      // Set Day-of-Week to SUNDAY
  rtc.setTime(11, 35, 0);     // Set the time to 12:00:00 (24hr format)
  rtc.setDate(29, 9, 2019);   // Set the date to September 29th, 2019

  lcd.init();// Inicializar el LCD
  lcd.backlight();//Encender la luz de fondo.
  lcd.clear();
  // Escribimos el Mensaje en el LCD.
  lcd.print("DS1302 + LCD16x2");
  lcd.setCursor(0,1);
  lcd.print("  MrChunckuee!  ");
  delay(1000); 
}

void loop(){
  unsigned long currentMillis = millis();
  if(currentMillis - previousMillis > interval) {
    // save the last time you blinked the LED 
    previousMillis = currentMillis;   
    // if the LED is off turn it on and vice-versa:
    if (ledState == LOW){
      ledState = HIGH;
      lcd.clear();
      lcd.print("Time:");
      lcd.setCursor(6,0);
      lcd.print(rtc.getTimeStr());
      lcd.setCursor(0,1);
      lcd.print("Date:");
      lcd.setCursor(6,1);
      lcd.print(rtc.getDateStr());
      }
      else
        ledState = LOW;
      // set the LED with the ledState of the variable:
      digitalWrite(pinLed, ledState);
      }
}
