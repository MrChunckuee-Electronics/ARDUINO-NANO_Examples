/*******************************************************************************
 *
 *        Mostrar datos del DS1302 y el DHT22 en una LCD16x2 
 *
 *******************************************************************************
 * FileName:        NANO_DS1302_DHT22_LCD16X2.ino
 * Processor:       ATmega328
 * Complier:        Arduino v1.8.9
 * Author:          Pedro Sánchez (MrChunckuee)
 * Blog:            http://mrchunckuee.blogspot.com/
 * Email:           mrchunckuee.psr@gmail.com
 * Description:     Ejemplo basico para mostrar datos leidos del DS1302 y un 
 *                  DHT22 en una LCD16x2, tambien puedes seleccionar mostar esos 
 *                  datos en el monitor serial (hay un bug, cada que tomamos 
 *                  lecturas del DHT22, hay un salto en los segundos mostrados, 
 *                  vere si en algun futuro lo corrijo).
 *******************************************************************************
 * Rev.         Date            Comment
 *   v0.0.0     06/03/2021      Creación del firmware
 ******************************************************************************/
#include <Wire.h> 
#include <DS1302.h>
#include <DHT.h>
#include <LiquidCrystal_I2C.h>

#define DHTPIN 14       //Pin A0 
#define DHTTYPE DHT22   // DHT11

#define USELCD 1 //Comentar para ver los valore en el monitor serial

DHT dht(DHTPIN, DHTTYPE);
DS1302 rtc(2, 3, 4); // Init the DS1302
LiquidCrystal_I2C lcd(0x27,16,2);  //Dirección  0x27 y 16 columnas x 2 filas

const int pinLed =  13;
int ledState = LOW;             // ledState used to set the LED
long previousMillis = 0;        // will store last time LED was updated
long interval = 500;           // interval at which to blink (milliseconds)
unsigned int count_millis = 0;
int sysFlagStatus = LOW;
int sysFlagInit = LOW;
unsigned char countSec = 0;
float temperatureDHT = 30.00; //Solo para que el primer valor no sea cero
float humidityDHT = 50.00;    //Solo para que el primer valor no sea cero

void setup(){
  pinMode(pinLed, OUTPUT);

  // Setup Serial connection
  Serial.begin(9600);
  
  // Set the clock to run-mode, and disable the write protection
  rtc.halt(false);
  rtc.writeProtect(false);
  // The following lines can be commented out to use the values already stored in the DS1302
  //rtc.setDOW(SATURDAY);      // Set Day-of-Week to FRIDAY
  //rtc.setTime(1, 12, 0);     // Set the time to 12:00:00 (24hr format)
  //rtc.setDate(6, 3, 2021);   // Set the date to August 6th, 2010

  dht.begin();      //Init DHT

  lcd.init();       // Inicializar el LCD
  lcd.backlight();  //Encender la luz de fondo.
  lcd.clear();
  
  #if defined USELCD // Escribimos mensaje en el LCD.
    lcd.print(" DHT22 + DS1302");
    lcd.setCursor(0,1);
    lcd.print("  MrChunckuee!  ");
  #else // Escribimos mensaje en el monitor serial.
    Serial.println("Testeando DHT22 + DS1302 + LCD16x2");
    Serial.println("https://mrchunckuee.blogspot.com/");
    Serial.println("MrChunckuee!");
  #endif
  delay(2000); //Solo por que me da hueva pensar en otra forma ahorita
}

void loop(){
  SENSOR_Update();
  unsigned long currentMillis = millis();
  if(currentMillis - previousMillis > interval) {
    // save the last time you blinked the LED 
    previousMillis = currentMillis;   
    // if the LED is off turn it on and vice-versa:
    if (ledState == LOW){
      ledState = HIGH;
      sysFlagStatus = HIGH;
      sysFlagInit = HIGH;
      }
      else
        ledState = LOW;
      // set the LED with the ledState of the variable:
      digitalWrite(pinLed, ledState);
      }
}

void SENSOR_Update (void){
  if (sysFlagStatus == HIGH){
    countSec++;
    if (countSec>2){ //Toma lectura cada 3 segundos
      countSec = 0;
      humidityDHT = dht.readHumidity();
      temperatureDHT = dht.readTemperature(); 
      }
      if(sysFlagInit = HIGH){
        //Serial or LCD
        #if defined USELCD
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print(rtc.getTimeStr());
          lcd.setCursor(11,0);
          lcd.print(temperatureDHT);
          lcd.setCursor(15,0);
          lcd.print("C");
          lcd.setCursor(0,1);
          lcd.print(rtc.getDateStr());
          lcd.setCursor(11,1);
          lcd.print(humidityDHT);
          lcd.setCursor(15,1);
          lcd.print("%");
        #else 
          Serial.print("Time: ");
          Serial.println(rtc.getTimeStr());
          Serial.print("Date: ");
          Serial.print(rtc.getDateStr());
          Serial.print(" ");
          Serial.println(rtc.getDOWStr());
          Serial.print("Temperature: ");
          Serial.print(temperatureDHT);
          Serial.println(" *C");
          Serial.print("Humidity: ");
          Serial.print(humidityDHT);
          Serial.println(" %");
          Serial.println(" ");
        #endif
      }
    sysFlagStatus = LOW;
  }
}
