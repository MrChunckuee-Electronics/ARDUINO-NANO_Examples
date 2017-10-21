/*******************************************************************************
 *
 *                  Multiplexar puerto serie
 *
 *******************************************************************************
 * FileName:        INO_007.ino
 * Processor:       ATmega328
 * Complier:        Arduino v1.8.3
 * Author:          Pedro Sánchez (MrChunckuee)
 * Blog:            http://mrchunckuee.blogspot.com/
 * Email:           mrchunckuee.psr@gmail.com
 * Description:     Programa para multiplexar el puerto serie del arduino nano, 
 *                  su funcion es basica, enviamos un dato por el modulo bluetooth
 *                  y dependiendo de este realizamos una accion y enviamos un
 *                  mensaje a la terminal serial de arduino por medio de un FT232
 *                  (esta mas que claro que la prioridad la tiene el bluetooth, 
 *                  aclaro que no pueden estar trabajando los dos modulos al 
 *                  mismo tiempo).
 *******************************************************************************
 * Rev.         Date            Comment
 *   v1.00      20/10/2017      Creación del firmware
 ******************************************************************************/
unsigned char inputByte = 0; // incoming serial byte
const int LED_Status = 13; //pin del LED
const int enableBluetooth = 2; //pin de control bluetooth
const int enableFT232 = 3; //pin de control FT232

void setup(){
  Serial.begin(9600);
  pinMode(LED_Status, OUTPUT);
  pinMode(enableBluetooth, OUTPUT);
  pinMode(enableFT232, OUTPUT);
  digitalWrite(enableBluetooth,HIGH); //Activamos opcion de bluetooth
  digitalWrite(enableFT232,LOW); //Apagamos opcion de FT232
}

void loop(){
  if (Serial.available() > 0) {
    inputByte = Serial.read(); // get incoming byte
    switch(inputByte){
      case 'a':
        digitalWrite(LED_Status,HIGH); 
        digitalWrite(enableBluetooth,LOW); //Apagamos bluetooth
        delay(3);
        digitalWrite(enableFT232,HIGH); //Activamos FT232
        delay(3);
        Serial.print("LED Rojo encendido\n"); //Enviamos por puerto del FT232
        delay(50);
        digitalWrite(enableFT232,LOW); //Apagamos opcion de FT232
        delay(3);
        digitalWrite(enableBluetooth,HIGH); //Activamos opcion de bluetooth
      break;
      case 'b':
        digitalWrite(LED_Status,LOW); 
        digitalWrite(enableBluetooth,LOW); //Apagamos bluetooth
        delay(3);
        digitalWrite(enableFT232,HIGH); //Activamos FT232
        delay(3);
        Serial.print("LED Rojo apagado\n"); //Enviamos por puerto del FT232
        delay(50);
        digitalWrite(enableFT232,LOW); //Apagamos opcion de FT232
        delay(3);
        digitalWrite(enableBluetooth,HIGH); //Activamos opcion de bluetooth
      break;
      default:
        digitalWrite(LED_Status,LOW); 
      break;
    }    
  }
}

