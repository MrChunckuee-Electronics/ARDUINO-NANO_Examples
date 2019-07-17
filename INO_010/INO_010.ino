/*******************************************************************************
 *
 *        Mostrar datos de teclado matricial 4x4 en LCD16x2 
 *
 *******************************************************************************
 * FileName:        INO_010.ino
 * Processor:       ATmega328
 * Complier:        Arduino v1.8.3
 * Author:          Pedro Sánchez (MrChunckuee)
 * Blog:            http://mrchunckuee.blogspot.com/
 * Email:           mrchunckuee.psr@gmail.com
 * Description:     Ejemplo basico para mostrar datos de teclado matricial 4x4 
 *                  en una LCD16x2.
 *******************************************************************************
 * Rev.         Date            Comment
 *   v0.0.0     16/07/2019      Creación del firmware
 ******************************************************************************/

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
 
const byte rowsCount = 4;
const byte columsCount = 4; // Se usa teclado 4x4
 
char keys[rowsCount][columsCount] = { //Se definen los valores de nuestra matriz
   { '1','2','3', 'A' },
   { '4','5','6', 'B' },
   { '7','8','9', 'C' },
   { '*','0','#', 'D' }
};
 
const byte rowPins[rowsCount] = { 12, 11, 10, 9 }; //Pines donde estan las filas
const byte columnPins[columsCount] = { 8, 7, 6, 5 }; //Punes donde estan las columnas

LiquidCrystal_I2C lcd(0x27,16,2);  //Dirección  0x27 y 16 columnas x 2 filas
Keypad keypad = Keypad(makeKeymap(keys), rowPins, columnPins, rowsCount, columsCount);
 
void setup() {
  lcd.init();// Inicializar el LCD
  lcd.backlight();//Encender la luz de fondo.
  lcd.clear();
  
  // Escribimos el Mensaje en el LCD.
  lcd.print("KeyPad + LCD16x2");
  lcd.setCursor(0,1);
  lcd.print("  MrChunckuee!  ");
  delay(2000); //Solo por que me da hueva pensar en otra forma ahorita
  lcd.clear();
  lcd.print("Pulsa un boton");
}
 
void loop() {
   char key = keypad.getKey(); //Se lee boton pulsado
   if (key) {
    lcd.setCursor(0,1); lcd.print(key); // Se muestra en (0,1) de la LCD
   }
}
