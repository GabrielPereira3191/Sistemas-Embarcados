

const int PIN_START = 2;  
const int PIN_STOP  = 3; 
const int PIN_S1 = 4;  
const int PIN_S2 = 5;  
const int PIN_S3 = 6;  
const int PIN_S4 = 7;  
const int PIN_M1 = 8;
const int PIN_C1 = 9;
const int PIN_C2 = 10;
const int PIN_LIGADA = 11;

const unsigned long TEMPO_ENCHIMENTO = 6000UL; 
const unsigned long TEMPO_C2_RECUO   = 1000UL;

enum Estado { IDLE, ALIMENTANDO, AGUARDA_S2, ENCHENDO, C2_RECUANDO, AGUARDA_S4 };
Estado estado = IDLE;

unsigned long tEstado = 0;
bool c2RecuoIniciado = false;
bool tempoIniciado = false;

void setup() {
  pinMode(PIN_START, INPUT_PULLUP);
  pinMode(PIN_STOP,  INPUT_PULLUP);
  pinMode(PIN_S1, INPUT_PULLUP);
  pinMode(PIN_S2, INPUT_PULLUP);
  pinMode(PIN_S3, INPUT_PULLUP);
  pinMode(PIN_S4, INPUT_PULLUP);

  pinMode(PIN_M1, OUTPUT);
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
    digitalWrite(PIN_C1, LOW);
    digitalWrite(PIN_C2, LOW);
    digitalWrite(PIN_LIGADA, LOW);
    c2RecuoIniciado = false;
    return;
  }

  switch (estado) {

    case IDLE:
      if (start) {
        digitalWrite(PIN_LIGADA, HIGH);
        digitalWrite(PIN_M1, HIGH);
        digitalWrite(PIN_C1, HIGH);
        estado = ALIMENTANDO;
      }
      break;

    case ALIMENTANDO:
      if (s1) {
        digitalWrite(PIN_C1, LOW); 
        estado = AGUARDA_S2;
      }
      break;

    case AGUARDA_S2:
      if (s2) {
        digitalWrite(PIN_M1, LOW);
        digitalWrite(PIN_C2, HIGH);
        estado = ENCHENDO;
      }
      break;

    case ENCHENDO:
      
      if (s3 && !tempoIniciado) {
        tEstado = millis();
        tempoIniciado = true;
      }
      if (tempoIniciado && (millis() - tEstado >= TEMPO_ENCHIMENTO)) {
        digitalWrite(PIN_C2, LOW);
        tempoIniciado = false;
        c2RecuoIniciado = false;
        estado = C2_RECUANDO;
      }
      break;

    case C2_RECUANDO:
      if (!c2RecuoIniciado) {
        tEstado = millis();
        c2RecuoIniciado = true;
      }
      if (millis() - tEstado >= TEMPO_C2_RECUO) {
        digitalWrite(PIN_M1, HIGH); 
        estado = AGUARDA_S4;
      }
      break;

    case AGUARDA_S4:
      if (s4) {
        digitalWrite(PIN_M1, LOW);
        digitalWrite(PIN_LIGADA, LOW);
        estado = IDLE; 
      }
      break;
  }
}
