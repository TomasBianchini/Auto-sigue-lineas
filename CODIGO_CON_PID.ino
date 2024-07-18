// Definir pines para el control del motor
// derecha
const int motorPin1 = 10;
const int motorPin2 = 11; 
const int enablePin1y2 = 9; 

const int motorPin3 = 6; 
const int motorPin4 = 5; 
const int enablePin3y4 = 3; 

const int sensorCentral = A0;
const int sensorDerecho = A1;
const int sensorIzquierdo = A2;

const int umbral = 500;

float  Kp = 0.7;  
float  Ki = 0.0008;         
float  Kd = 0.7;

int ultError = 0;
int P;
int I;
int D;

int velBase = 70;

void setup() {
  // configurar pines como salidas 
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(enablePin1y2, OUTPUT);
  pinMode(motorPin3, OUTPUT);
  pinMode(motorPin4, OUTPUT);
  pinMode(enablePin3y4, OUTPUT);

  // configurar pines de sensores como entrada
  pinMode(sensorCentral, INPUT);

  
  // Inicializar motor y LEDs apagados
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, LOW);
  digitalWrite(enablePin1y2, LOW);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, LOW);
  digitalWrite(enablePin3y4, LOW);
  
  Serial.begin(9600);
}


void loop() {
  control_PID();
}

// función para gestionar velocidad y direccion del motor
void control_auto(int vd,int vi) {
  if(vd < 0) {
    digitalWrite(motorPin1, LOW);
  	digitalWrite(motorPin2, HIGH);
    vd = -vd;
  } else {
    digitalWrite(motorPin1, HIGH);
  	digitalWrite(motorPin2, LOW);
  }
  
  if(vi < 0) {
    digitalWrite(motorPin3, LOW);
  	digitalWrite(motorPin4, HIGH);
    vi = -vi;
  } else {
    digitalWrite(motorPin3, HIGH);
  	digitalWrite(motorPin4, LOW);
  }
  
  analogWrite(enablePin1y2, vd);  
  analogWrite(enablePin3y4, vi);
}

// velocidad con controlador PID
void control_PID() {
  int valorCentral = analogRead(sensorCentral);
  int valorDerecho = analogRead(sensorDerecho);
  int valorIzquierdo = analogRead(sensorIzquierdo);
  
  int ubi = ubicacion(valorDerecho,valorCentral,valorIzquierdo);
  
  int error = 1000 - ubi;

  
  P = error;
  I = I + error;
  D = error - ultError;
  
  ultError = error;
  
  int vel = P*Kp + I*Ki + D*Kd;
  Serial.println(vel);
  int motorD = velBase - vel;
  int motorI = velBase +  vel;
  
  if (motorD > 110) {
    motorD = 110;
  }
  if (motorI > 110) {
    motorI = 110;
  }
  if (motorD < -70) {
    motorD = -70;
  }
  if (motorI < -70)  {
    motorI = -70;
  } 

  control_auto(motorD,motorI);
  
}


int ubicacion(int d,int c, int i){
  
  long pos = 0L * d + 1000L * c + 2000L * i;
  pos = pos /(d+c+i);
  
  return pos;
}