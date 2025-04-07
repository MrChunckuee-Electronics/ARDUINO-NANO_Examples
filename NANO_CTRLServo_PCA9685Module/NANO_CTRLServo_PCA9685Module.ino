/*******************************************************************************
 *
 *  Control de servomotores con el modulo PCA9685
 *
 *******************************************************************************
 * FileName:        NANO_CTRLServo_PCA9685Module.ino
 * Processor:       ATmega328
 * Complier:        Arduino v1.8.19
 * Author:          Pedro Sánchez (MrChunckuee)
 * Blog:            http://mrchunckuee.blogspot.com/
 * Email:           mrchunckuee.psr@gmail.com
 * Description:     Control de servomotores Vigor y Futaba con el modulo I2C 
 *                  PCA9685 desde el monitor serial de Arduino.
 *******************************************************************************
 * Rev.         Date            Comment
 *   v1.0.0     06/04/2025      Prueba de la libreria de adafruit.
 ******************************************************************************/
 
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver servos = Adafruit_PWMServoDriver(0x40);

//Servo VIGOR VS-2
unsigned int maxPWM_Duty = 505;
unsigned int minPWM_Duty = 130;

//Servo FUTABA S3003
//unsigned int maxPWM_Duty = 245;
//unsigned int minPWM_Duty = 120;

   
bool updateFlag = false, autoFlag = false;  
uint8_t ServoNumber;
uint16_t ServoAngle;
String serialDataString;
uint8_t rxDataBuffer[14] = {0};

void setup() {
  servos.begin();  
  servos.setPWMFreq(50); 
  Serial.begin(9600);
  showTextInit();
  servosInit();
}

void servosInit(void){
  for(char x=0; x<16; x++){
    setPosServo(x, 0);
    delay(50);
  }
}

/*
 * Funcion para setear el servo, acepta parametros de canal y angulo.
 */
void setPosServo(uint8_t n_servo, int angulo) {
  int duty = map(angulo, 0, 180, minPWM_Duty, maxPWM_Duty);
  servos.setPWM(n_servo, 0, duty);  
}

/*
 *  SerialEvent occurs whenever a new data comes in the hardware serial RX. 
 *  This routine is run between each time loop() runs, so using delay inside loop can delay response. 
 *  Multiple bytes of data may be available.
 */
void serialEvent(void) { //Servo14=120
  if (Serial.available()) { // if there is data comming
      serialDataString = Serial.readStringUntil('\n'); // read string until newline character
      serialDataString.toCharArray(rxDataBuffer, serialDataString.length()+1);
      ServoNumber = ((rxDataBuffer[5]-0x30)*10) + (rxDataBuffer[6]-0x30);
      ServoAngle = ((rxDataBuffer[8]-0x30)*10) + ((rxDataBuffer[9]-0x30)*10) + (rxDataBuffer[10]-0x30);
      Serial.println(serialDataString);
      if(serialDataString == "AUTO"){
        autoFlag = true;
      }
      else{
        autoFlag = false;
      }
      updateFlag = true;
  }
}

/*
 * Muestra informacion de uso.
 */
void showTextInit(void){
  Serial.println("Arduino + PCA9685 Driver");
  Serial.println("mrchunckuee.blogspot.com");
  Serial.println("Forma de uso:");
  Serial.println("Tipear ServoX=POS, donde X=canal y POS=posicion en angulos de 0 a 180");
  Serial.println("El numero del servo es a dos diguitos, ejem. Servo00, Servo05... Servo15");
  Serial.println("La posicion debe ser de tres digitos ejem. 000, 058, 180.");
}

void loop() {
  if(updateFlag){
    if(autoFlag){
            setPosServo(0, 45);
            setPosServo(1, 45);
            setPosServo(8, 45);
            setPosServo(9, 45);
            delay(1000);
            setPosServo(0, 90);
            setPosServo(1, 90);
            setPosServo(8, 90);
            setPosServo(9, 90);
            delay(1000);
            setPosServo(0, 180);
            setPosServo(1, 180);
            setPosServo(8, 180);
            setPosServo(9, 180);
            delay(1000);
    }
    else{
      setPosServo(ServoNumber, ServoAngle);
      updateFlag = false;
    }
  }
}
