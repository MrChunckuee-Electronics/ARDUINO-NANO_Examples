/*******************************************************************************
 *
 *                  IR Remote Control - Activar cargas
 *
 *******************************************************************************
 * FileName:        NANO_IRremote_CtrlRelay.ino
 * Processor:       ATmega328
 * Complier:        Arduino v1.6.5
 * Author:          Pedro Sánchez (MrChunckuee)
 * Blog:            http://mrchunckuee.blogspot.com/
 * Email:           mrchunckuee.psr@gmail.com
 * Description:     Activado 2 Reles y 2 LEDs con control remoto
 *******************************************************************************
 * Rev.         Date            Comment
 *   v1.00      14/04/2016      Creación del firmware
 ******************************************************************************/
#include <IRremote.h> //Incluir la libreria 

int RECV_PIN = 11; // Entrada IR
int LED_1 = 2;
int LED_2 = 3;
int RELE_FOCO = 4;
int RELE_MOTOR = 5;

// Valores para control IR Xinda
//       Tecla       ValorHEX
#define BUTTON_1     0xFF6897
#define BUTTON_2     0xFF9867
#define BUTTON_3     0xFFB04F
#define BUTTON_4     0xFF30CF
#define BUTTON_5     0xFF18E7
#define BUTTON_6     0xFF7A85
#define BUTTON_7     0xFF10EF
#define BUTTON_8     0xFF38C7
#define BUTTON_9     0xFF5AA5
#define BUTTON_0     0xFF4AB5

//Es necesario para que funcione la libreria
IRrecv irrecv(RECV_PIN);
decode_results results;

void setup() {
  // Declaramos entradas y salidas
  pinMode(LED_1,OUTPUT);
  pinMode(LED_2,OUTPUT);
  pinMode(RELE_FOCO,OUTPUT);
  pinMode(RELE_MOTOR,OUTPUT);
  irrecv.enableIRIn(); // Start the receiver
}

void loop() {
  // Checamos si se recibio algun dato
  if (irrecv.decode(&results)){
    // Evaluamos el dato recibido
    // Realizamos la accion correspondiente
    switch (results.value){
      case BUTTON_1:
        digitalWrite(LED_1, HIGH);
        break;
      case BUTTON_2:
        digitalWrite(LED_1, LOW);
        break;
      case BUTTON_3:
        digitalWrite(LED_2, HIGH);
        break;
      case BUTTON_4:
        digitalWrite(LED_2, LOW);
        break;
      case BUTTON_5:
        digitalWrite(RELE_FOCO, HIGH);
        break;
      case BUTTON_6:
        digitalWrite(RELE_FOCO, LOW);
        break;
      case BUTTON_7:
        digitalWrite(RELE_MOTOR, HIGH);
        break;
      case BUTTON_8:
        digitalWrite(RELE_MOTOR, LOW);
        break;
      case BUTTON_9:
        digitalWrite(LED_1, HIGH);
        digitalWrite(LED_2, HIGH);
        digitalWrite(RELE_FOCO, HIGH);
        digitalWrite(RELE_MOTOR, HIGH);
        break;
      case BUTTON_0:
        digitalWrite(LED_1, LOW);
        digitalWrite(LED_2, LOW);
        digitalWrite(RELE_FOCO, LOW);
        digitalWrite(RELE_MOTOR, LOW);
        break;
      default:
        break;
      }
      delay(10); 
      irrecv.resume(); // Receive the next value
      }
}
