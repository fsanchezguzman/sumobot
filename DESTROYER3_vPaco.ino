/*ROBOT DE SUMO CON ULTRASONIDOS. REVISADO POR FSANCHEZGUZMAN
Configurado el setup según las reglas de Robocampeones. Espera 5 segundos y retrocede buscando la línea negra de borde. 
El DOJO de combate debe ser blanco con línea de borde negra.
Este robot debe tener dos sensores IR y un sensor HC-SR04 de ultrasonidos.
Además, funciona con servomotores de 360º.
*/
//Basado en el código de programación by DioniSantidrian is licensed under the Creative Commons - Attribution - Non-Commercial license.
//visit https://www.thingiverse.com/thing:2835619 for more information

//AL COMIENZO DEL PROGRAMA DEFINIMOS EN QUE PINES IRAN CONECTADOS LOS DISTINTOS DISPOSITIVOS
const int sensorD = 4;    // sensor D delantero al pin 4
const int sensorIR = 2;          //sensor IR delantero al pin 2
const int motorIzquierdo = 10;       //servomotor Izquierdo al pin 10
const int motorDerecho = 9;        //servomotor Derecho al pin 9
//The analog input pins can be used as digital pins w/ numbers 14 (analog input 0) to 19 (analog input 5)
const int echo = 16;           //Sensor ultrasonidos pin A2
const int trigger = 17;          //Sensor ultrasonidos pin A3

const int distanciaMaxima = 40;        // Esta será la distancia de detección del robot en CM

//ANTES DE ARRANCAR EL PROGRAMA, CARGAMOS LAS SIGUIENTES LIBRERIAS PARA FACILITAR LA LABOR
#include <Servo.h>
#include <NewPing.h>

//ESTE CODIGO ES PARA INICIALIZAR LAS LIBRERIAS
Servo servoDerecho;   //Se inicia un servo con el nombre servoDerecho
Servo servoIzquierdo; //Se inicia un servo con el nombre servoIzquierdo
NewPing sonar(trigger, echo, distanciaMaxima); //Se inicia el sensor de ultrasonidos

//DECLARAMOS UNA SERIE DE VARIABLES PARA HACER EL PROGRAMA MAS LEGIBLE Y PRÁCTICO
//boolean modoCombate = false;  // Inicializamos la variable para que el robot comience parado

int estadoSensorIR;
int estadoSensorD; //Variable que almacena el estado del sensor Izquierdo
unsigned int cm;           //Variable para medir la distancia con el sensor de ultrasonidos
//unsigned int uS;  //Variable que no hace falta definir. para medir la distancia con el sensor de ultrasonidos

//ESTA FUNCION LEE LOS SENSORES DEL ROBOT
void leerSensores() {

  estadoSensorIR = digitalRead(sensorIR); //Lee el sensor de linea IR
  estadoSensorD = digitalRead(sensorD); //Lee el sensor de linea D
  //Lee el sensor de ultrasonidos en centimetros
  cm = sonar.ping_cm();

}

//SETUP FUNCIONA UNA SOLA VEZ AL INICIO DEL PROGRAMA
//LA USAREMOS PARA CONFIGURAR LA FUNCION DE CADA PIN
void setup() {
  pinMode(sensorIR, INPUT);//El pin sera una entrada para leer el sensor de linea
  pinMode(sensorD, INPUT);//El pin sera una entrada para leer el sensor de linea
  pinMode(echo, INPUT);     //El pin sera una entrada para leer el sensor de ultrasonidos
  pinMode(trigger, OUTPUT); //El pin enviara señales ultrasónicas, será una salida.

  servoDerecho.attach(motorDerecho);      //El pin va a manejar un servo
  servoIzquierdo.attach(motorIzquierdo);  //El pin va a manejar un servo
  Parado();                              //empezamos parados 5 segundos
  //esperamos 5 segundos antes de empezar
  delay(5000);
  // vamos marcha atrás en dirección al borde
  Atras();
  delay(500);
  Parado();
  delay(100);
  GirarIzquierda();
  delay(1000); //controlar el delay para que el giro sea de 180º y se ponga mirando a la línea negra del borde.
  Parado();
  delay(100);
  //estadoSensorIR = 1;
  do
  {
    leerSensores();
    Despacio();
  }  while (estadoSensorIR == 1);
}

//LA FUNCION LOOP SE REPITE CONSTANTEMENTE, ES EL CORAZON DEL PROGRAMA
void loop() {

  delay(50);      //Hacemos una pequeña pausa para estabilizar el programa

  leerSensores(); //Leemos los sensores de ultrasonidos y de linea

  if ((estadoSensorIR == LOW) || (estadoSensorD == LOW)) //Si alguno de los sensores DETECTA LA LINEA
    Evasion();  //Esquiva la linea

  if (cm != 0)  //DETECTA UN ENEMIGO, ya que el sensor envía un 0 si no detecta nada dentro de la distanciaMaxima definida de 40 cm.
    Adelante(); //Ataca moviendose hacia delante

  else
    GirarDerecha();//BUSCA AL ENEMIGO
}

//A PARTIR DE AQUI TODO SON MANIOBRAS DE MOVIMIENTO
void GirarDerecha() {
  servoDerecho.write(60); //gira despacio porque está buscando
  servoIzquierdo.write(60);
  delay(50);
}
void GirarIzquierda() {
  servoDerecho.write(180);
  servoIzquierdo.write(180);
  delay(50);
}
void Adelante() {
  servoDerecho.write(180);
  servoIzquierdo.write(0);
}

void Despacio() {

  servoDerecho.write(135);
  servoIzquierdo.write(45);
  delay(50);
}

void Atras() {

  servoDerecho.write(0);
  servoIzquierdo.write(180);
  delay(50);
}

void Parado() {
  servoDerecho.write(90);
  servoIzquierdo.write(90);
  delay(50);
}

void Evasion() {
  Parado();
  delay(200);
  Atras();
  delay(2000); //Poner los segundos necesarios para alejarse de la línea lo bastante.
  Parado();
  delay(100);
}







