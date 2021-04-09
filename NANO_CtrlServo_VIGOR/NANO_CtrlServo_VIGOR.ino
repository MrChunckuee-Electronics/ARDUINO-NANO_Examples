/*******************************************************************************
 *
 *                  Manejo de servomotor
 *
 *******************************************************************************
 * FileName:        NANO_CtrlServo_VIGOR.ino
 * Processor:       ATmega328
 * Complier:        Arduino v1.6.5
 * Author:          Pedro Sánchez (MrChunckuee)
 * Blog:            http://mrchunckuee.blogspot.com/
 * Email:           mrchunckuee.psr@gmail.com
 * Description:     Barrido automatico de un servo VIGOR VS-2 
 *                  El servo trabaja con pulsos que van desde 800 a 2200us
 *******************************************************************************
 * Rev.         Date            Comment
 *   v1.00      23/07/2016      Creación del firmware
 ******************************************************************************/
#include <Servo.h> 
Servo myservo; 
int pos = 0;    // Variable para la posición del servo 
 
void setup() { 
  myservo.attach(2);  //Servo en D2
} 
 
void loop() {
  // De 800 a 2200us por que es el rango en el que trabaja el servo
  // Incrementamos o decrementamos en 5, pero igual puede variar el valor
  // incluso se puede variar el retardo
  for(pos = 800; pos <= 2200; pos += 5){                                  
    myservo.writeMicroseconds(pos); //Enviamos la posición del servo    
    delay(10); // Pequeño retardo antes de cambiar a la nueva posición                      
  }
  for(pos = 2200; pos>=800; pos-=5){                                
    myservo.writeMicroseconds(pos);             
    delay(10);                       
  } 
} 

