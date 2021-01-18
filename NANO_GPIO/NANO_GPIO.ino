/*******************************************************************************
 *
 *                  Uso de entradas y salidas
 *
 *******************************************************************************
 * FileName:        NANO_GPIO.ino
 * Processor:       ATmega328
 * Complier:        Arduino v1.6.5
 * Author:          Pedro Sánchez (MrChunckuee)
 * Blog:            http://mrchunckuee.blogspot.com/
 * Email:           mrchunckuee.psr@gmail.com
 * Description:     Manejo basico de entradas y salidas usando Arduino Nano(Chino)
 *******************************************************************************
 * Rev.         Date            Comment
 *   v1.00      14/10/2015      Creación del firmware
 ******************************************************************************/
// Etiquetas de entradas y salidas 
// mover de acuerdo al circuito
int BOTON_1 = 2;
int BOTON_2 = 3;
int BOTON_3 = 4;
int BOTON_4 = 5;
int LED_1 = 6;
int LED_2 = 7;
int LED_3 = 8; 
int LED_4 = 9;

void setup() {
  //Declaramos entradas y salidas
  pinMode(BOTON_1, INPUT);
  pinMode(BOTON_2, INPUT);
  pinMode(BOTON_3, INPUT);
  pinMode(BOTON_4, INPUT);
  pinMode(LED_1, OUTPUT);
  pinMode(LED_2, OUTPUT);
  pinMode(LED_3, OUTPUT);
  pinMode(LED_4, OUTPUT); 
}

void loop() {
  //Checamos entras y activamos salidas dependiendo del estado
  if (digitalRead(BOTON_1)==HIGH) digitalWrite(LED_1, HIGH);
  else digitalWrite(LED_1, LOW);
  if (digitalRead(BOTON_2)==HIGH) digitalWrite(LED_2, HIGH);
  else digitalWrite(LED_2, LOW);
  if (digitalRead(BOTON_3)==HIGH) digitalWrite(LED_3, HIGH);
  else digitalWrite(LED_3, LOW);
  if (digitalRead(BOTON_4)==HIGH) digitalWrite(LED_4, HIGH);
  else digitalWrite(LED_4, LOW);
}
