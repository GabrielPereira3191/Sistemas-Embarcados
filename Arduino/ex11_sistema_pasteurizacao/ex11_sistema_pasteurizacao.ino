

const int PIN_START = 2; 
const int PIN_STOP  = 3;  
const int PIN_S1 = 4; 
const int PIN_S2 = 5; 
const int PIN_S3 = 6; 
const int PIN_S4 = 7; 

const int PIN_M1 = 8;  
const int PIN_R1 = 9; 
const int PIN_V1 = 10; 
const int PIN_LIGADA = 11;

const unsigned long TEMPO_AQUECIMENTO   = 3000UL;
const unsigned long TEMPO_RESFRIAMENTO  = 3000UL;

enum Estado { IDLE, ESPERA_S1, ESPERA_S2, AQUECENDO, ESPERA_S3, RESFRIANDO, ESPERA_S4 };
Estado estado = IDLE;

unsigned long tEstado = 0;
bool timerIniciado = false;

void setup() {
  pinMode(PIN_START, INPUT_PULLUP);
  pinMode(PIN_STOP,  INPUT_PULLUP);
  pinMode(PIN_S1, INPUT_PULLUP);
  pinMode(PIN_S2, INPUT_PULLUP);
  pinMode(PIN_S3, INPUT_PULLUP);
  pinMode(PIN_S4, INPUT_PULLUP);

  pinMode(PIN_M1, OUTPUT);
  pinMode(PIN_R1, OUTPUT);
  pinMode(PIN_V1, OUTPUT);
  pinMode(PIN_LIGADA, OUTPUT);
}

void loop() {
  bool start = (digitalRead(PIN_START) == LOW);
  bool stop  = (digitalRead(PIN_STOP)  == LOW);
  bool s1 = (digitalRead(PIN_S1) == LOW);
  bool s2 = (digitalRead(PIN_S2) == LOW);
  bool s3 = (digitalRead(PIN_S3) == LOW);
  bool s4 = (digitalRead(PIN_S4) == LOW);

  if (stop) {
    estado = IDLE;
    digitalWrite(PIN_M1, LOW);
    digitalWrite(PIN_R1, LOW);
    digitalWrite(PIN_V1, LOW);
    digitalWrite(PIN_LIGADA, LOW);
    timerIniciado = false;
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
        estado = ESPERA_S2;
      }
      break;

    case ESPERA_S2:
      if (s2) {
        digitalWrite(PIN_M1, LOW);
        digitalWrite(PIN_R1, HIGH);
        tEstado = millis();
        estado = AQUECENDO;
      }
      break;

    case AQUECENDO:
      if (millis() - tEstado >= TEMPO_AQUECIMENTO) {
        digitalWrite(PIN_R1, LOW);
        digitalWrite(PIN_M1, HIGH);
        estado = ESPERA_S3;
      }
      break;

    case ESPERA_S3:
      if (s3) {
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
        estado = ESPERA_S4;
      }
      break;

    case ESPERA_S4:
      if (s4) {
        digitalWrite(PIN_M1, LOW);
        digitalWrite(PIN_LIGADA, LOW);
        estado = IDLE; 
      }
      break;
  }
}
