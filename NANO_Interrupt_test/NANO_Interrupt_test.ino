/*******************************************************************************
 *
 *        Ejemplo basico usando timers e interrupciones
 *
 *******************************************************************************
 * FileName:        NANO_Interrupt_test.ino
 * Processor:       ATmega328
 * Complier:        Arduino v1.8.3
 * Author:          Pedro Sánchez (MrChunckuee)
 * Blog:            http://mrchunckuee.blogspot.com/
 * Email:           mrchunckuee.psr@gmail.com
 * Description:     Encender LEDs cada determinado tiempo, usando el TIMER1
 *******************************************************************************
 * Rev.         Date            Comment
 *   v0.0.0     23/03/2019      Creación del firmware
 ******************************************************************************/
const int button    = 2;
const int ctrlLed1  = 3;
const int ctrlLed2  = 4;
const int ctrlLed3  = 5;
const int ctrlLed4  = 6;
const int ctrlLed5  = 7;
const int ctrlLed6  = 8;
const int ctrlLed7  = 9;
const int ctrlLed8  = 10;
const int ctrlLed9  = 11;
const int ctrlLed10 = 12;
const int ledStatus = 13;

unsigned char pinCount;
unsigned int buttonState = 0, buttonTicks = 0;
unsigned int currentButtonState = 0, lastButtonState = 0;
boolean buttonFlag = false, buttonMode = false;
unsigned int contador = 0, segundos = 0;
// Valor en segundos del conteo
// Si se requiere mas tiempo se puede hacer
// Este valor pondra fin al conteno del TIMER1
unsigned int tiempoTotal = 120; 

void setup() {
  pinMode(button, INPUT);
  for(pinCount = 3; pinCount <14; pinCount++)
      pinMode(pinCount, OUTPUT);
      
  //Clear all outputs
  for(pinCount = 3; pinCount <14; pinCount++)
      digitalWrite(pinCount, LOW);
      
  // Se inicializa el TIMER1 
  TIMER1_Init();
  delay(50);
}

ISR(TIMER1_OVF_vect){
  TCNT1 = 49911;  // preload timer
  contador++;
  if (contador>4){
    contador = 0;
    segundos++;
    if (segundos>tiempoTotal){
      segundos = 0;
      //Clear all outputs
      for(pinCount = 3; pinCount <14; pinCount++){
        digitalWrite(pinCount, LOW);
        }
      TIMER1_Disable();
      buttonFlag = false;
      buttonMode = false;
    }
    digitalWrite(ledStatus, digitalRead(ledStatus) ^ 1);
  }
} 

void GetInput(void){
  // Push Button debounce
  if (buttonState != digitalRead(button)){
    if (buttonTicks > 20){
      buttonState = digitalRead(button);
      buttonTicks = 0;
      }
      else buttonTicks++;
  }
  else buttonTicks = 0;
  // Process the push button
  currentButtonState = buttonState;
  if (currentButtonState == 0 && lastButtonState == 1){
      buttonFlag = true;
  }
  lastButtonState = currentButtonState;   
}

void TIMER1_Init(void){
  /* Consideraciones para el calculo:
   *  T = periodo del timer, f = frecuencia del clock = 16MHz  
   *  T = 1/f --> 1/16MHz = 0.0625us
   *  TiempoOverflowTIMER1 = T * (65536 - PreloadTimer) * Prescaler
   *        = 0.0625us * (65536 - 49911) * 256
   *        = 0.24 segundos
   */
  cli();  // Stop interrupts
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 =  49911;           // preload timer 65536-16MHz/256/4Hz
  TCCR1B |= (1 << CS12);    // 256 prescaler 
  sei();  //Allow interrupts
}

void TIMER1_Enable(void){
  // Enable timer overflow interrupt
  TIMSK1 |= (1 << TOIE1);   
}

void TIMER1_Disable(void){
  // Disable timer overflow interrupt
  TIMSK1 &= ~(1 << TOIE1);   
}

void loop() {
  GetInput();
  if (buttonFlag == true){
    if (buttonMode == false){
      buttonMode = true;
      TIMER1_Enable();
    }
    // Puedes encender el LED en el segundo deseado
    // Puedes apagar el LED en el segundo deseado
    switch(segundos){
      case 2:
        digitalWrite(ctrlLed10, HIGH);
      break;
      case 5:
        digitalWrite(ctrlLed1, HIGH);
      break;
      case 8:
        digitalWrite(ctrlLed1, LOW);
      break;
      
      case 10:
        digitalWrite(ctrlLed2, HIGH);
      break;
      case 12:
        digitalWrite(ctrlLed3, HIGH);
        digitalWrite(ctrlLed4, HIGH);
      break;
      case 30: 
        digitalWrite(ctrlLed2, LOW);
      break;
      case 45: 
        digitalWrite(ctrlLed3, LOW);
      break;
      case 50: 
        digitalWrite(ctrlLed2, LOW);
        digitalWrite(ctrlLed4, LOW);
      break;
      case 61: 
        digitalWrite(ctrlLed5, HIGH);
        digitalWrite(ctrlLed6, HIGH);
      break;
      case 80: 
        digitalWrite(ctrlLed6, LOW);
      break;
      case 89: 
        digitalWrite(ctrlLed5, LOW);
      break;
      case 90: 
        digitalWrite(ctrlLed7, HIGH);
        digitalWrite(ctrlLed8, HIGH);
      break;
      case 100: 
        digitalWrite(ctrlLed9, HIGH);
      break;    
      case 105: 
        digitalWrite(ctrlLed8, LOW);
      break;
      case 110: 
        digitalWrite(ctrlLed7, LOW);
        digitalWrite(ctrlLed9, LOW);
      break;
      case 112: 
        for(pinCount = 3; pinCount <14; pinCount++)
            digitalWrite(pinCount, HIGH);
      break;
      case 118: 
        for(pinCount = 3; pinCount <14; pinCount++)
            digitalWrite(pinCount, LOW);
      break;
      default:
      break;
    }
  }
}
