

const int PIN_START = 2;  
const int PIN_STOP  = 3; 
const int PIN_S1 = 4;     
const int PIN_S2 = 5;     
const int PIN_S3 = 6;     
const int PIN_S4 = 7;     

const int PIN_M1 = 8;
const int PIN_M2 = 9;
const int PIN_C1 = 10;
const int PIN_C2 = 11;
const int PIN_LIGADA = 12;

const unsigned long TEMPO_RECUO = 1000UL;

enum Estado { IDLE, ESPERA_PECA, C1_AVANCA, C2_AVANCA, M2_RUN, RECUANDO };
Estado estado = IDLE;

unsigned long tRecuo = 0;

void setup() {
  pinMode(PIN_START, INPUT_PULLUP);
  pinMode(PIN_STOP,  INPUT_PULLUP);
  pinMode(PIN_S1, INPUT_PULLUP);
  pinMode(PIN_S2, INPUT_PULLUP);
  pinMode(PIN_S3, INPUT_PULLUP);
  pinMode(PIN_S4, INPUT_PULLUP);

  pinMode(PIN_M1, OUTPUT);
  pinMode(PIN_M2, OUTPUT);
  pinMode(PIN_C1, OUTPUT);
  pinMode(PIN_C2, OUTPUT);
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
    digitalWrite(PIN_M2, LOW);
    digitalWrite(PIN_C1, LOW);
    digitalWrite(PIN_C2, LOW);
    digitalWrite(PIN_LIGADA, LOW);
    return;
  }

  switch (estado) {

    case IDLE:
      if (start) {
        digitalWrite(PIN_LIGADA, HIGH);
        digitalWrite(PIN_M1, HIGH);
        estado = ESPERA_PECA;
      }
      break;

    case ESPERA_PECA:
      if (s2) {
        digitalWrite(PIN_M1, LOW);
        digitalWrite(PIN_C1, HIGH);
        estado = C1_AVANCA;
      }
      break;

    case C1_AVANCA:
      if (s1) {
        digitalWrite(PIN_C2, HIGH);
        estado = C2_AVANCA;
      }
      break;

    case C2_AVANCA:
      if (s3) {
        digitalWrite(PIN_M2, HIGH); 
        estado = M2_RUN;
      }
      break;

    case M2_RUN:
      if (s4) {
        digitalWrite(PIN_M2, LOW);
        digitalWrite(PIN_C1, LOW);
        digitalWrite(PIN_C2, LOW);
        tRecuo = millis();
        estado = RECUANDO;
      }
      break;

    case RECUANDO:
      
      if (millis() - tRecuo >= TEMPO_RECUO) {
        digitalWrite(PIN_LIGADA, LOW);
        estado = IDLE; 
      }
      break;
  }
}
