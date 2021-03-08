/*******************************************************************************
 *
 *        Menú básico con teclado matricial 4x4 y LCD16x2
 *
 *******************************************************************************
 * FileName:        NANO_KeyPad4x4_LCD16x2_menu.ino
 * Processor:       ATmega328
 * Complier:        Arduino v1.8.9
 * Author:          Pedro Sánchez (MrChunckuee)
 * Blog:            http://mrchunckuee.blogspot.com/
 * Email:           mrchunckuee.psr@gmail.com
 * Description:     Ejemplo basico para hacer un pequeño menu, dentro de este 
 *                  tenemos dos tareas, la primera encender y la segunda apagar 
 *                  un LED, en este caso es el que incorpora la tarjeta
 *******************************************************************************
 * Rev.         Date            Comment
 *   v1.0.0     07/03/2021      Creación del firmware
 ******************************************************************************/
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>

#define BTN_UP    0
#define BTN_DOWN  1
#define tMAX      1 //Tareas maximas en este caso vale 1 por que el cero cuenta

const byte rowsCount = 4;
const byte columsCount = 4;

//Definimos nuesra keypad
char keys[rowsCount][columsCount] = {
   { '1','2','3', 'A' },
   { '4','5','6', 'B' },
   { '7','8','9', 'C' },
   { '*','0','#', 'D' }
};

// Pattern del curson flecha
byte cursorArrow[8]  = {B10000, B11000, B11100, B11110, B11100, B11000, B10000};
 
const byte rowPins[rowsCount] = { 12, 11, 10, 9 };
const byte columnPins[columsCount] = { 8, 7, 6, 5 };

LiquidCrystal_I2C lcd(0x27,16,2);  //Dirección  0x27 y 16 columnas x 2 filas
Keypad keypad = Keypad(makeKeymap(keys), rowPins, columnPins, rowsCount, columsCount);

const int pinLed =  13; //Defaul LED on board arduino nano

char buttonPresed;
 
void setup() {
  pinMode(pinLed, OUTPUT);
  
  // Setup Serial connection
  Serial.begin(9600);

  lcd.init();// Inicializar el LCD
  lcd.backlight();//Encender la luz de fondo.
  lcd.clear();

  // Escribimos el Mensaje en el LCD.
  lcd.print("KeyPad + LCD16x2");
  lcd.setCursor(0,1);
  lcd.print("  MrChunckuee!  ");
  delay(2000); //Solo por que me da hueva pensar en otra forma ahorita

  // Se añaden los caracteres especiales al objeto LCD:
  lcd.createChar (0,cursorArrow);

  lcd.clear();
}
 
void loop() {
  lcd.setCursor(0,0); lcd.print("Menu MrChunckuee");
  lcd.setCursor(0,1); lcd.print("    Pulse A     ");
  buttonPresed = keypad.getKey();
  if (buttonPresed == 'A')
      MENU_Options();
}

void MENU_Options (void) {
  int posCursor = 0, opcMenu = -5;
  
  // Menu
  lcd.clear();
  lcd.setCursor(2, 0); lcd.print("Encender LED");
  lcd.setCursor(2, 1); lcd.print("Apagar LED");
  
  do{
    buttonPresed = keypad.getKey();
    
    // Cursor que indica la opcion seleccioanda:
    lcd.setCursor(0, posCursor); 
    lcd.write(byte (0)); //Pintamos flecha en LCD

    if(buttonPresed == 'B')
        MENU_MueveCursor(&posCursor, tMAX, BTN_DOWN);
    else if(buttonPresed == 'C')
        MENU_MueveCursor(&posCursor, tMAX, BTN_UP);
    else if(buttonPresed == '*')
        opcMenu = posCursor;
    else if(buttonPresed == 'D')
        opcMenu = -3;
    
    switch(opcMenu){
      case 0:       
        MENU_Option1();
        opcMenu = -5;
        break;
      case 1:     
        MENU_Option2();
        opcMenu = -5;
        break;
      default:
        break;
    }
  }while (opcMenu != -3);
}

//Esta rutina posiciona el cursor (flecha) em la linea deseada
void MENU_MueveCursor(int *pos, int max, char ope){
  if(ope)
    if(*pos < max)  *pos += 1;
    else      *pos = 0;
  else
    if(*pos > 0)  *pos -= 1;
    else      *pos = max;

  // Se borran los cursores:
  lcd.setCursor(0, 0); lcd.print(" ");
  lcd.setCursor(0, 1); lcd.print(" ");
}

//Funcion que hace la tarea uno
void MENU_Option1(void){
  digitalWrite(pinLed, HIGH);
  }

//Funcion que hace la tarea dos
void MENU_Option2(void){
  digitalWrite(pinLed, LOW);
  }
