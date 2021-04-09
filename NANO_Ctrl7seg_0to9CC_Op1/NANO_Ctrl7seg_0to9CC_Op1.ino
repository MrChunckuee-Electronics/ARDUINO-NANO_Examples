/*******************************************************************************
 *
 *  Control de display de 7 segmentos de catodo comun - Contador de 0 a 9 (Op.1)
 *
 *******************************************************************************
 * FileName:        NANO_Ctrl7seg_0to9CC_op1.ino
 * Processor:       ATmega328
 * Complier:        Arduino v1.8.42
 * Author:          Pedro Sánchez (MrChunckuee)
 * Blog:            http://mrchunckuee.blogspot.com/
 * Email:           mrchunckuee.psr@gmail.com
 * Description:     Control de un display de 7 segmentos de catodo comun (opcion 
 *                  uno), utilizo el modulo de 7 segmentos antes mostrado en el blog.
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

// Arreglo de los pines donde esta conectado el display
const int segments[7] = {
                         displaySegmentoA, 
                         displaySegmentoB,
                         displaySegmentoC,
                         displaySegmentoD,
                         displaySegmentoE,
                         displaySegmentoF,
                         displaySegmentoG
                         };

// Arreglo de datos para los numeros
// el orden de los datos es el siguiente: G F E D C B A
const byte numbers[10] = {
                          0b0111111,     //0
                          0b0000110,     //1
                          0b1011011,     //2
                          0b1001111,     //3
                          0b1100110,     //4
                          0b1101101,     //5
                          0b1111101,     //6
                          0b0000111,     //7
                          0b1111111,     //8
                          0b1100111      //9
                          };

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
  digitalWrite(displayTransistorUnidad, LOW); 
}

void loop() {
  contador++;
  if( contador>maxNumCounter)
    contador = 0;
  display7SEG_Update(numbers[contador]);
  delay(500);
}

/*******************************************************************************
 * Function:        void display7SEG_Update(byte numero)
 * Description:     Esta función pone en alto el pin del display a utlizar y pasa 
 *                  el parametro numero a display7SEG_Show. 
 * Precondition:    None
 * Parameters:      byte numero: Dato/Numero a mostrar 
 * Return Values:   None
 * Remarks:         None
 * *****************************************************************************/
void display7SEG_Update(byte numero){
  digitalWrite(displayTransistorUnidad, HIGH); 
  display7SEG_Show(numero);
}

/*******************************************************************************
 * Function:        void display7SEG_Show(byte numero)
 * Description:     Esta función actualiza los pines de cada segmento
 * Precondition:    None
 * Parameters:      byte numero: Dato/Numero a mostrar 
 * Return Values:   None
 * Remarks:         None
 * *****************************************************************************/
void display7SEG_Show(byte numero){
   for (int x = 0; x < 7; x++) {
    int bitShow = bitRead(numero, x);
    digitalWrite(segments[x], bitShow);
   }
}
