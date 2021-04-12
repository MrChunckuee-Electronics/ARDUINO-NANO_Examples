/*******************************************************************************
 *
 *  Control de display de 7 segmentos de catodo comun - Contador de 0 a 9 (Op.2)
 *
 *******************************************************************************
 * FileName:        NANO_Ctrl7seg_0to9CC_op1.ino
 * Processor:       ATmega328
 * Complier:        Arduino v1.8.42
 * Author:          Pedro Sánchez (MrChunckuee)
 * Blog:            http://mrchunckuee.blogspot.com/
 * Email:           mrchunckuee.psr@gmail.com
 * Description:     Control de un display de 7 segmentos de catodo comun (opcion 
 *                  dos), utilizo el modulo de 7 segmentos antes mostrado en el blog.
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
}

void loop() {
  contador++;
  if( contador>maxNumCounter)
    contador = 0;
  display7SEG_Update(contador);
  delay(500);
}

/*******************************************************************************
 * Function:        void display7SEG_Update(char numero)
 * Description:     Esta función toma el parametro numero y lo pone en display7SEG_Show 
 *                  Envia estados (1 y 0) al display dependiendo del numero a mostrar
 * Precondition:    None
 * Parameters:      byte numero: Dato/Numero a mostrar 
 * Return Values:   None
 * Remarks:         None
 * *****************************************************************************/
void display7SEG_Update(char numero){
    switch (numero){
      case 0:
        display7SEG_Show(1, 1, 1, 1, 1, 1, 0); 
        break;
      case 1:
        display7SEG_Show(0, 1, 1, 0, 0, 0, 0); 
        break;
      case 2:
        display7SEG_Show(1, 1, 0, 1, 1, 0, 1); 
        break;
      case 3:
        display7SEG_Show(1, 1, 1, 1, 0, 0, 1); 
        break;
      case 4:
        display7SEG_Show(0, 1, 1, 0, 0, 1, 1); 
        break;
      case 5:
        display7SEG_Show(1, 0, 1, 1, 0, 1, 1); 
        break;
      case 6:
        display7SEG_Show(1, 0, 1, 1, 1, 1, 1); 
        break;
      case 7:
        display7SEG_Show(1, 1, 1, 0, 0, 0, 0); 
        break;
      case 8:
        display7SEG_Show(1, 1, 1, 1, 1, 1, 1); 
        break;
      case 9:
        display7SEG_Show(1, 1, 1, 0, 0, 1, 1); 
        break;
      default:
        break;
    } 
}

/*******************************************************************************
 * Function:        void display7SEG_Show(int valueSegA, int valueSegB, int valueSegC, 
                                          int valueSegD, int valueSegE, int valueSegF, 
                                          int valueSegG)
 * Description:     Esta función actualiza los pines de cada segmento.
 * Precondition:    None
 * Parameters:      int valueSeg A-F: Valor de cada segmento
 * Return Values:   None
 * Remarks:         None
 * *****************************************************************************/
void display7SEG_Show(int valueSegA, int valueSegB, int valueSegC, 
                      int valueSegD, int valueSegE, int valueSegF, 
                      int valueSegG){
    digitalWrite(displayTransistorUnidad, HIGH);
    digitalWrite(displaySegmentoA, valueSegA);  
    digitalWrite(displaySegmentoB, valueSegB);  
    digitalWrite(displaySegmentoC, valueSegC);  
    digitalWrite(displaySegmentoD, valueSegD);  
    digitalWrite(displaySegmentoE, valueSegE);  
    digitalWrite(displaySegmentoF, valueSegF);  
    digitalWrite(displaySegmentoG, valueSegG);  
}
