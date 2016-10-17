/*******************************************************************************
 *
 *                  Sensor ultrasónico HC-SR04
 *
 *******************************************************************************
 * FileName:        INO_005.ino
 * Processor:       ATmega328
 * Complier:        Arduino v1.6.5
 * Author:          Pedro Sánchez (MrChunckuee)
 * Blog:            http://mrchunckuee.blogspot.com/
 * Email:           mrchunckuee.psr@gmail.com
 * Description:     Monitoreo del sensor ultrasónico HC-SR04, la distancia 
 *                  entregada es con dos decimales.
 *******************************************************************************
 * Rev.         Date            Comment
 *   v1.00      23/07/2016      Creación del firmware
 ******************************************************************************/
int pinECHO = 3; // Pin echo en D3
int pinTRIG = 4; // Pin trig en D4
float distancia; // Variable para guardar la distancia

void setup(){
  Serial.begin(9600); // Puerto serie a 9600 baudios
  pinMode(pinTRIG, OUTPUT); 
  pinMode(pinECHO, INPUT); 
}

void loop(){
  distancia = GetDistance();
  // Si estamos dentro del rango medible mostramos la distancia
  if(distancia >= 2 && distancia<=450){
    Serial.print("Distancia: ");
    Serial.print(distancia);
    Serial.println(" cm");
  }
  else Serial.println("Fuera de rango");
  delay(200);
}

float GetDistance(){
  float distance, tiempo;
  digitalWrite(pinTRIG,HIGH);
  delayMicroseconds(10);
  digitalWrite(pinTRIG, LOW);
  tiempo = pulseIn(pinECHO, HIGH);
  distance = tiempo / 58.00; // Distancia con 2 decimales
  return distance;
}

