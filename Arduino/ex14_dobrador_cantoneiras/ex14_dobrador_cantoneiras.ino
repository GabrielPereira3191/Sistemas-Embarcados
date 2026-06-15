

const int PIN_START = 2;  
const int PIN_STOP  = 3;  
const int PIN_S1 = 4; 
const int PIN_S2 = 5;  
const int PIN_S3 = 6;  
const int PIN_S4 = 7; 

const int PIN_M1 = 8;
const int PIN_C1 = 9;  
const int PIN_C2 = 10; 
const int PIN_C3 = 11; 
const int PIN_LIGADA = 12;

const unsigned long ESPERA_2S = 2000UL;
const unsigned long TEMPO_RECUO = 1000UL; 

enum Estado {
  IDLE, ESPERA_S4, C1_AVANCA, ESPERA_2S_1,
  C3_AVANCA, ESPERA_2S_2, C2_AVANCA, RECUANDO
};
Estado estado = IDLE;

unsigned long tEstado = 0;

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
  pinMode(PIN_C3, OUTPUT);
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
    digitalWrite(PIN_C3, LOW);
    digitalWrite(PIN_LIGADA, LOW);
    return;
  }

  switch (estado) {

    case IDLE:
      if (start) {
        digitalWrite(PIN_LIGADA, HIGH);
        digitalWrite(PIN_M1, HIGH);
        estado = ESPERA_S4;
      }
      break;

    case ESPERA_S4:
      if (s4) {
        digitalWrite(PIN_M1, LOW);
        digitalWrite(PIN_C1, HIGH); 
        estado = C1_AVANCA;
      }
      break;

    case C1_AVANCA:
      if (s1) {
        tEstado = millis();
        estado = ESPERA_2S_1;
      }
      break;

    case ESPERA_2S_1:
      if (millis() - tEstado >= ESPERA_2S) {
        digitalWrite(PIN_C3, HIGH); 
        estado = C3_AVANCA;
      }
      break;

    case C3_AVANCA:
      if (s3) {
        tEstado = millis();
        estado = ESPERA_2S_2;
      }
      break;

    case ESPERA_2S_2:
      if (millis() - tEstado >= ESPERA_2S) {
        digitalWrite(PIN_C2, HIGH); 
        estado = C2_AVANCA;
      }
      break;

    case C2_AVANCA:
      if (s2) {
        
        digitalWrite(PIN_C1, LOW);
        digitalWrite(PIN_C2, LOW);
        digitalWrite(PIN_C3, LOW);
        tEstado = millis();
        estado = RECUANDO;
      }
      break;

    case RECUANDO:
      if (millis() - tEstado >= TEMPO_RECUO) {
        digitalWrite(PIN_LIGADA, LOW);
        estado = IDLE; 
      }
      break;
  }
}
