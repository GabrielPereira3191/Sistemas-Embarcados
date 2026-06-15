

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

const unsigned long TEMPO_C1 = 1000UL;     
const unsigned long TEMPO_C2 = 1000UL;     
const unsigned long TEMPO_QUEDA_GRANDE = 1500UL; 

enum Estado {
  IDLE, C1_ALIMENTA, ESTEIRA_RUN,
  C2_EMPURRA, C2_RECUA, GRANDE_AGUARDA, RECUANDO_C1
};
Estado estado = IDLE;

unsigned long tEstado = 0;
bool pecaGrande = false;

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
  bool s2 = (digitalRead(PIN_S2) == LOW);
  bool s3 = (digitalRead(PIN_S3) == LOW);
  bool s4 = (digitalRead(PIN_S4) == LOW);

  if (stop) {
    estado = IDLE;
    digitalWrite(PIN_M1, LOW);
    digitalWrite(PIN_C1, LOW);
    digitalWrite(PIN_C2, LOW);
    digitalWrite(PIN_LIGADA, LOW);
    return;
  }

  switch (estado) {

    case IDLE:
      if (start) {
        digitalWrite(PIN_LIGADA, HIGH);
        digitalWrite(PIN_C1, HIGH);
        pecaGrande = false;
        tEstado = millis();
        estado = C1_ALIMENTA;
      }
      break;

    case C1_ALIMENTA:
      if (millis() - tEstado >= TEMPO_C1) {
        digitalWrite(PIN_C1, LOW);
        digitalWrite(PIN_M1, HIGH);
        estado = ESTEIRA_RUN;
      }
      break;

    case ESTEIRA_RUN:
      
      if (s2 || s3) pecaGrande = true;

      if (pecaGrande) {
        
        tEstado = millis();
        estado = GRANDE_AGUARDA;
      } else if (s4) {
        
        digitalWrite(PIN_M1, LOW);
        digitalWrite(PIN_C2, HIGH);
        tEstado = millis();
        estado = C2_EMPURRA;
      }
      break;

    case GRANDE_AGUARDA:
      if (millis() - tEstado >= TEMPO_QUEDA_GRANDE) {
        digitalWrite(PIN_M1, LOW);
        estado = RECUANDO_C1;
      }
      break;

    case C2_EMPURRA:
      if (millis() - tEstado >= TEMPO_C2) {
        digitalWrite(PIN_C2, LOW);
        tEstado = millis();
        estado = C2_RECUA;
      }
      break;

    case C2_RECUA:
      if (millis() - tEstado >= TEMPO_C2) {
        estado = RECUANDO_C1;
      }
      break;

    case RECUANDO_C1:
      
      digitalWrite(PIN_LIGADA, LOW);
      estado = IDLE;
      break;
  }
}
