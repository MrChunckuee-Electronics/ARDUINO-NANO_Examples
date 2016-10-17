/*******************************************************************************
 *
 *                  Control de servomotor con potenciometro
 *
 *******************************************************************************
 * FileName:        INO_006.ino
 * Processor:       ATmega328
 * Complier:        Arduino v1.6.5
 * Author:          Pedro Sánchez (MrChunckuee)
 * Blog:            http://mrchunckuee.blogspot.com/
 * Email:           mrchunckuee.psr@gmail.com
 * Description:     Programa para controlar la posición de un servo VIGOR VS-2
 *                  con ayuda de un potenciometro
 *******************************************************************************
 * Rev.         Date            Comment
 *   v1.00      06/08/2016      Creación del firmware
 ******************************************************************************/
#include <Servo.h> 
Servo myservo; 
const int pinPOT = A2; // Pin del potenciometro
const int pinSERVO = 2; // Pin del servo (Esta en D2)
int pos = 0;    // Variable para la posicion del servo 
int valPOT = 0; // Variable para el valor del ADC
 
void setup() { 
  myservo.attach(pinSERVO);
} 
 
void loop() {
  valPOT = analogRead(pinPOT); // Leemos el valor del ADC
  pos = map(valPOT, 0, 1023, 800, 2200); // Convertimos los valores del potenciometro a los del servo
  myservo.writeMicroseconds(pos); // Escribimos posicion 
  delay(15); //Pequeño retardo antes de leer otro valor             
} 
