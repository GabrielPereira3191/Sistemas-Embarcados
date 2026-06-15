

const int PIN_START = 2;  
const int PIN_STOP  = 3;  
const int PIN_S1 = 4; 
const int PIN_S2 = 5;
const int PIN_S3 = 6;  

const int PIN_M1 = 7;
const int PIN_M2 = 8;
const int PIN_LIGADA = 9;
const int PIN_LIMITE = 10; 

const int LIMITE_PECAS = 5;

enum Estado { IDLE, ESPERA_S1, M1_RUN, M2_RUN, LIMITE_ATINGIDO };
Estado estado = IDLE;

int contadorPecas = 0;

void setup() {
  pinMode(PIN_START, INPUT_PULLUP);
  pinMode(PIN_STOP,  INPUT_PULLUP);
  pinMode(PIN_S1, INPUT_PULLUP);
  pinMode(PIN_S2, INPUT_PULLUP);
  pinMode(PIN_S3, INPUT_PULLUP);

  pinMode(PIN_M1, OUTPUT);
  pinMode(PIN_M2, OUTPUT);
  pinMode(PIN_LIGADA, OUTPUT);
  pinMode(PIN_LIMITE, OUTPUT);
}

void loop() {
  bool start = (digitalRead(PIN_START) == LOW);
  bool stop  = (digitalRead(PIN_STOP)  == LOW);
  bool s1 = (digitalRead(PIN_S1) == LOW);
  bool s2 = (digitalRead(PIN_S2) == LOW);
  bool s3 = (digitalRead(PIN_S3) == LOW);

  if (stop) {
    estado = IDLE;
    digitalWrite(PIN_M1, LOW);
    digitalWrite(PIN_M2, LOW);
    digitalWrite(PIN_LIGADA, LOW);
    digitalWrite(PIN_LIMITE, LOW);
    contadorPecas = 0; 
    return;
  }

  switch (estado) {

    case IDLE:
      if (start) {
        digitalWrite(PIN_LIGADA, HIGH);
        estado = ESPERA_S1;
      }
      break;

    case ESPERA_S1:
      if (s1) {
        digitalWrite(PIN_M1, HIGH);
        estado = M1_RUN;
      }
      break;

    case M1_RUN:
      if (s2) {
        digitalWrite(PIN_M1, LOW);
        digitalWrite(PIN_M2, HIGH);
        estado = M2_RUN;
      }
      break;

    case M2_RUN:
      if (s3) {
        digitalWrite(PIN_M2, LOW);
        contadorPecas++;

        if (contadorPecas >= LIMITE_PECAS) {
          digitalWrite(PIN_LIMITE, HIGH);
          estado = LIMITE_ATINGIDO;
        } else {
          
          estado = ESPERA_S1;
        }
      }
      break;

    case LIMITE_ATINGIDO:
      
      break;
  }
}
