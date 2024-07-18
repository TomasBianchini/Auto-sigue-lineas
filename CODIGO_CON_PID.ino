
// Motor izquierda
int i3 = 10;
int i4 = 11; 
int enableI = 9; 
// Motor derecha
int i2 = 6; 
int i1 = 5; 
int enableD = 3; 


int sCentro = A0;
int sDerecha = A1;
int sIzquierda = A2;


float  Kp = 0.7;  
float  Ki = 0.0008;         
float  Kd = 0.7;

int ultError = 0;
int P;
int I;
int D;

int velBase = 70;

void setup() {

  pinMode(i3, OUTPUT);
  pinMode(i4, OUTPUT);
  pinMode(enableI, OUTPUT);
  pinMode(i2, OUTPUT);
  pinMode(i1, OUTPUT);
  pinMode(enableD, OUTPUT);

  pinMode(sCentro, INPUT);
  pinMode(sDerecha, INPUT);
  pinMode(sIzquierda, INPUT);

 
  digitalWrite(i3, LOW);
  digitalWrite(i4, LOW);
  digitalWrite(enableI, LOW);
  digitalWrite(i2, LOW);
  digitalWrite(i1, LOW);
  digitalWrite(enableD, LOW);
  
}


void loop() {
  int valorC = analogRead(sCentro);
  int valorD = analogRead(sDerecha);
  int valorI = analogRead(sIzquierda);
  
  int ubi = posicion(valorD,valorC,valorI);
  
  int error = 1000 - ubi;

  
  P = error;
  I = I + error;
  D = error - ultError;
  
  ultError = error;
  
  int vel = P*Kp + I*Ki + D*Kd;

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

  velocidad(motorD,motorI);
}


void velocidad(int vd,int vi) {
  if(vd < 0) {
    digitalWrite(i3, LOW);
  	digitalWrite(i4, HIGH);
    vd = -vd;
  } else {
    digitalWrite(i3, HIGH);
  	digitalWrite(i4, LOW);
  }
  
  if(vi < 0) {
    digitalWrite(i2, LOW);
  	digitalWrite(i1, HIGH);
    vi = -vi;
  } else {
    digitalWrite(i2, HIGH);
  	digitalWrite(i1, LOW);
  }
  
  analogWrite(enableI, vd);  
  analogWrite(enableD, vi);
}



int posicion(int d,int c, int i){
  
  long pos = 0L * d + 1000L * c + 2000L * i;
  pos = pos /(d+c+i);
  
  return pos;
}