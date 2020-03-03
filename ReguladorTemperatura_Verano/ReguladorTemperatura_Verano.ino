/*
  Este programa consiste en que cuando se activa el arduino, saca el promedio de la temperatura ambiental (con 3 mediciones para que sea lo más preciso posible)
  y si es alta según el usuario (y la versión*), enciende de forma automática el aire acondicionado.

  No solamente eso sino que luego de 5 minutos de que el aire esté en funcionamiento, y mediante la misma función, se hace un promedio de la temperatura ambiental
  nuevamente. 
  
  ¿Con qué fin?
  
    Simple. Para que en caso de que haya alguna puerta o ventana abierta el dispositivo apague el aire acondicionado automáticamente para ahorrar energía.


    * : Esta es la versión de verano, que incluye sistemas para temperaturas elevadas. En caso de que sea invierno se debe usar dicha versión que será implementada
         aproximadamente en Marzo luego de corroborar la eficacia del dispositivo y verificar si se puede complementar eficazmente con la estufa.
*/

#include <Servo.h>

#define sensor A0
#define relay 5           //Relay ubicado en el cable de la estufa o reemplazando al switch.
#define pin_servo 3

Servo servo;

byte suma = 0;
int medidas[2];
int lectura, samples;
byte temperatura, nueva_medida;
boolean encendido;      // Siempre que reinice el programa va a estar en false. Así puede encender el aire solo cuando yo lo reinicie. Puede automatizarse con la hora.

void setup() {
  servo.attach(pin_servo, 900, 2100);
  encendido = false;
  //pinMode(relay, OUTPUT);
}

void loop() {

  temperatura = promedio();
  
  if(temperatura >= 27 && !encendido)         //Si hace mucho calor/frío prende el relay que puede reemplazar al botón del aire acondicionado/estufa.
  {
    //digitalWrite(relay, HIGH);      
    servo.write(45);
    delay(500);
    servo.write(0);
    encendido = true;     //esta variable sirve para que solo se active una vez en vez de estar todo el tiempo prendiendo y apagando.
  }
  delay(300000);

  nueva_medida = promedio();
  
  if(nueva_medida + 2 > temperatura)
  {
     servo.write(45);
     delay(500);
     servo.write(0);
  }
  delay(5000);
}


//Sistema de promedio de mediciones:
    

int promedio()
{
   for (int i = 0; i < 3; i++)
   {
       medidas[i] = analogRead(sensor) * 0.48828125;
       suma += medidas[i];
       delay(5000);      
       samples ++;      //Si quiero tomar más muestras o menos solo tengo que modificar el numero del for.
   }
      
   int promedio = (medidas[0]+ medidas[1] + medidas[2]) / samples;
   
   return promedio;      
}  