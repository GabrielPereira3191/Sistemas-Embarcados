

const int PIN_START = 2;  
const int PIN_STOP  = 3;  
const int PIN_S1 = 4;  
const int PIN_S2 = 5;  
const int PIN_S3 = 6;  

const int PIN_M1 = 7;
const int PIN_C1 = 8;
const int PIN_V1 = 9; 
const int PIN_LIGADA = 10;

const unsigned long TEMPO_RESFRIAMENTO = 5000UL; 

enum Estado { IDLE, C1_AVANCA, ESPERA_S2, RESFRIANDO, ESPERA_S3 };
Estado estado = IDLE;

unsigned long tEstado = 0;

void setup() {
  pinMode(PIN_START, INPUT_PULLUP);
  pinMode(PIN_STOP,  INPUT_PULLUP);
  pinMode(PIN_S1, INPUT_PULLUP);
  pinMode(PIN_S2, INPUT_PULLUP);
  pinMode(PIN_S3, INPUT_PULLUP);

  pinMode(PIN_M1, OUTPUT);
  pinMode(PIN_C1, OUTPUT);
  pinMode(PIN_V1, OUTPUT);
  pinMode(PIN_LIGADA, OUTPUT);
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
    digitalWrite(PIN_C1, LOW);
    digitalWrite(PIN_V1, LOW);
    digitalWrite(PIN_LIGADA, LOW);
    return;
  }

  switch (estado) {

    case IDLE:
      if (start) {
        digitalWrite(PIN_LIGADA, HIGH);
        digitalWrite(PIN_M1, HIGH);
        digitalWrite(PIN_C1, HIGH);
        estado = C1_AVANCA;
      }
      break;

    case C1_AVANCA:
      if (s1) {
        digitalWrite(PIN_C1, LOW);
        estado = ESPERA_S2;
      }
      break;

    case ESPERA_S2:
      if (s2) {
        digitalWrite(PIN_M1, LOW);
        digitalWrite(PIN_V1, HIGH);
        tEstado = millis();
        estado = RESFRIANDO;
      }
      break;

    case RESFRIANDO:
      if (millis() - tEstado >= TEMPO_RESFRIAMENTO) {
        digitalWrite(PIN_V1, LOW);
        digitalWrite(PIN_M1, HIGH);
        estado = ESPERA_S3;
      }
      break;

    case ESPERA_S3:
      if (s3) {
        digitalWrite(PIN_M1, LOW);
        digitalWrite(PIN_LIGADA, LOW);
        estado = IDLE; 
      }
      break;
  }
}
