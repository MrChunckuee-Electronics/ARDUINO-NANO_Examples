/*******************************************************************************
 *
 *        Ejemplo basico de la LCD16x2 con el modulo I2C
 *
 *******************************************************************************
 * FileName:        NANO_LCD12x6_I2C_test.ino
 * Processor:       ATmega328
 * Complier:        Arduino v1.8.3
 * Author:          Pedro Sánchez (MrChunckuee)
 * Blog:            http://mrchunckuee.blogspot.com/
 * Email:           mrchunckuee.psr@gmail.com
 * Description:     Ejemplo basico para mostrar mensajes en una LCD 16x2 con I2C 
 *******************************************************************************
 * Rev.         Date            Comment
 *   v0.0.0     07/07/2019      Creación del firmware
 ******************************************************************************/

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

//Crear el objeto lcd  dirección  0x27 y 16 columnas x 2 filas
LiquidCrystal_I2C lcd(0x27,16,2);  //

void setup() {
  // Inicializar el LCD
  lcd.init();
  
  //Encender la luz de fondo.
  lcd.backlight();
  
  // Escribimos el Mensaje en el LCD.
  lcd.print("Hola Mundo");
  lcd.setCursor(0, 1);
  lcd.print("LCD16x2 con I2C");

  delay(2000);
  lcd.clear(); //Limpiamos pantalla
  lcd.print("Contador");
}

void loop() {
   // Ubicamos el cursor en la primera posición(columna:0) de la segunda línea(fila:1)
  lcd.setCursor(0, 1);
   // Escribimos el número de segundos trascurridos
  lcd.print(millis()/1000);
  lcd.print(" Segundos");
  delay(100);
}
