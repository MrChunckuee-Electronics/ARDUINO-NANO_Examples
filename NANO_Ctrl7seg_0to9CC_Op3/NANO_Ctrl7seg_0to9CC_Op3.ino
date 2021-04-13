/*******************************************************************************
 *
 *  Control de display de 7 segmentos de catodo comun - Contador de 0 a 9 (Op.3)
 *
 *******************************************************************************
 * FileName:        NANO_Ctrl7seg_0to9CC_op3.ino
 * Processor:       ATmega328
 * Complier:        Arduino v1.8.42
 * Author:          Pedro Sánchez (MrChunckuee)
 * Blog:            http://mrchunckuee.blogspot.com/
 * Email:           mrchunckuee.psr@gmail.com
 * Description:     Control de un display de 7 segmentos de catodo comun (opcion 
 *                  tres), utilizo el modulo de 7 segmentos antes mostrado en el blog.
 *******************************************************************************
 * Rev.         Date            Comment
 *   v1.0.0     08/04/2021      Creación del firmware
 ******************************************************************************/
#define displaySegmentoA 2
#define displaySegmentoB 3
#define displaySegmentoC 4
#define displaySegmentoD 5
#define displaySegmentoE 6
#define displaySegmentoF 7
#define displaySegmentoG 8

#define displayTransistorUnidad 9

#define maxNumCounter 9 //Valor maximo ce cuenta

int contador;
char display_value[4];
unsigned char display_count;

void setup() {               
  pinMode(displaySegmentoA, OUTPUT);  
  pinMode(displaySegmentoB, OUTPUT);  
  pinMode(displaySegmentoC, OUTPUT);  
  pinMode(displaySegmentoD, OUTPUT);  
  pinMode(displaySegmentoE, OUTPUT);  
  pinMode(displaySegmentoF, OUTPUT);  
  pinMode(displaySegmentoG, OUTPUT); 
  pinMode(displayTransistorUnidad, OUTPUT);  
  contador = 0;
  digitalWrite(displayTransistorUnidad, 0);
  display7SEG_Clear();
}

void loop() {
    contador++;
    if( contador>maxNumCounter)
      contador = 0;
    display7SEG_SetNumero(contador);
    display7SEG_Update();
    delay(500);
}

/*******************************************************************************
 * Function:        void display7SEG_Clear()
 * Description:     Esta función coloca en cero la variable display_value.
 * Precondition:    None
 * Parameters:      None
 * Return Values:   None
 * Remarks:         None
 * *****************************************************************************/
void display7SEG_Clear(){
  display_value[3]='0';
  display_value[2]='0';
  display_value[1]='0';
  display_value[0]='0';
  display7SEG_Update();
}

/*******************************************************************************
 * Function:        void display7SEG_SetNumero(int numero)
 * Description:     Esta función convierte de int a char (valor a caracter).
 * Precondition:    None
 * Parameters:      int numero: Dato/Numero a covertir
 * Return Values:   None
 * Remarks:         None
 * *****************************************************************************/
void display7SEG_SetNumero(int numero){
  itoa (numero, display_value, 10);
}

/*******************************************************************************
 * Function:        void display7SEG_Update(byte numero)
 * Description:     Esta función pone en alto el pin del display a utlizar y 
 *                  actualiza los displays con el numero a mostrar.
 * Precondition:    None
 * Parameters:      None
 * Return Values:   None
 * Remarks:         display_value[0]-0x30; se debe a que itoa pasa una int a char
 *                  asi que le restamos 0x30 para obtener los numeros (ASCII).
 * *****************************************************************************/
void display7SEG_Update(){
  digitalWrite(displayTransistorUnidad, 1); 
  display7SEG_Show(display_value[0]-0x30);
}

/*******************************************************************************
 * Function:        void display7SEG_Show(char numero)
 * Description:     Esta función actualiza los pines de cada segmento
 * Precondition:    None
 * Parameters:      byte numero: Dato/Numero a mostrar 
 * Return Values:   None
 * Remarks:         None
 * *****************************************************************************/
void display7SEG_Show(char numero){
  switch (numero) {
      case 1:
        digitalWrite(displaySegmentoA, 0);
        digitalWrite(displaySegmentoB, 1);
        digitalWrite(displaySegmentoC, 1);
        digitalWrite(displaySegmentoD, 0);
        digitalWrite(displaySegmentoE, 0);
        digitalWrite(displaySegmentoF, 0);
        digitalWrite(displaySegmentoG, 0);
        break;
      case 2:                
        digitalWrite(displaySegmentoA, 1);
        digitalWrite(displaySegmentoB, 1);
        digitalWrite(displaySegmentoC, 0);
        digitalWrite(displaySegmentoD, 1);
        digitalWrite(displaySegmentoE, 1);
        digitalWrite(displaySegmentoF, 0);
        digitalWrite(displaySegmentoG, 1);
        break;      
      case 3:               
        digitalWrite(displaySegmentoA, 1);
        digitalWrite(displaySegmentoB, 1);
        digitalWrite(displaySegmentoC, 1);
        digitalWrite(displaySegmentoD, 1);
        digitalWrite(displaySegmentoE, 0);
        digitalWrite(displaySegmentoF, 0);
        digitalWrite(displaySegmentoG, 1);
        break;
      case 4:               
        digitalWrite(displaySegmentoA, 0);
        digitalWrite(displaySegmentoB, 1);
        digitalWrite(displaySegmentoC, 1);
        digitalWrite(displaySegmentoD, 0);
        digitalWrite(displaySegmentoE, 0);
        digitalWrite(displaySegmentoF, 1);
        digitalWrite(displaySegmentoG, 1);
        break;
      case 5:              
        digitalWrite(displaySegmentoA, 1);
        digitalWrite(displaySegmentoB, 0);
        digitalWrite(displaySegmentoC, 1);
        digitalWrite(displaySegmentoD, 1);
        digitalWrite(displaySegmentoE, 0);
        digitalWrite(displaySegmentoF, 1);
        digitalWrite(displaySegmentoG, 1);
        break;
      case 6:               
        digitalWrite(displaySegmentoA, 1);
        digitalWrite(displaySegmentoB, 0);
        digitalWrite(displaySegmentoC, 1);
        digitalWrite(displaySegmentoD, 1);
        digitalWrite(displaySegmentoE, 1);
        digitalWrite(displaySegmentoF, 1);
        digitalWrite(displaySegmentoG, 1);
        break;
      case 7:             
        digitalWrite(displaySegmentoA, 1);
        digitalWrite(displaySegmentoB, 1);
        digitalWrite(displaySegmentoC, 1);
        digitalWrite(displaySegmentoD, 0);
        digitalWrite(displaySegmentoE, 0);
        digitalWrite(displaySegmentoF, 0);
        digitalWrite(displaySegmentoG, 0);
        break;
      case 8:             
        digitalWrite(displaySegmentoA, 1);
        digitalWrite(displaySegmentoB, 1);
        digitalWrite(displaySegmentoC, 1);
        digitalWrite(displaySegmentoD, 1);
        digitalWrite(displaySegmentoE, 1);
        digitalWrite(displaySegmentoF, 1);
        digitalWrite(displaySegmentoG, 1);
        break;
      case 9:               
        digitalWrite(displaySegmentoA, 1);
        digitalWrite(displaySegmentoB, 1);
        digitalWrite(displaySegmentoC, 1);
        digitalWrite(displaySegmentoD, 0);
        digitalWrite(displaySegmentoE, 0);
        digitalWrite(displaySegmentoF, 1);
        digitalWrite(displaySegmentoG, 1);
        break;
      case 0:                
         digitalWrite(displaySegmentoA, 1);
         digitalWrite(displaySegmentoB, 1);
         digitalWrite(displaySegmentoC, 1);
         digitalWrite(displaySegmentoD, 1);
         digitalWrite(displaySegmentoE, 1);
         digitalWrite(displaySegmentoF, 1);
         digitalWrite(displaySegmentoG, 0);
         break;
      default: 
         digitalWrite(displaySegmentoA, 0);
         digitalWrite(displaySegmentoB, 0);
         digitalWrite(displaySegmentoC, 0);
         digitalWrite(displaySegmentoD, 0);
         digitalWrite(displaySegmentoE, 0);
         digitalWrite(displaySegmentoF, 0);
         digitalWrite(displaySegmentoG, 0);
         break;
    }
}
