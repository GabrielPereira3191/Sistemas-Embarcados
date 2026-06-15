
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

const unsigned long TEMPO_C2   = 1000UL;
const unsigned long TEMPO_RESET = 1000UL;

enum Estado { IDLE, ESPERA_PECA, C1_AVANCA, ANALISA_MATERIAL, C2_DESVIA, FINALIZA };
Estado estado = IDLE;

unsigned long tEstado = 0;
bool finalizaIniciado = false;

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
  bool s2_metal    = (digitalRead(PIN_S2) == LOW);
  bool s3_plastico = (digitalRead(PIN_S3) == LOW);
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
        estado = ESPERA_PECA;
      }
      break;

    case ESPERA_PECA:
      if (s1) {
        digitalWrite(PIN_C1, HIGH); 
        estado = C1_AVANCA;
      }
      break;

    case C1_AVANCA:
      if (s4) {
        estado = ANALISA_MATERIAL;
      }
      break;

    case ANALISA_MATERIAL:
      if (s2_metal) {
        
        digitalWrite(PIN_C2, HIGH);
        tEstado = millis();
        estado = C2_DESVIA;
      } else {
        
        estado = FINALIZA;
      }
      break;

    case C2_DESVIA:
      if (millis() - tEstado >= TEMPO_C2) {
        digitalWrite(PIN_C2, LOW);
        estado = FINALIZA;
      }
      break;

    case FINALIZA:
      
      if (!finalizaIniciado) {
        digitalWrite(PIN_M1, HIGH);
        digitalWrite(PIN_C1, LOW);
        tEstado = millis();
        finalizaIniciado = true;
      }
      if (millis() - tEstado >= TEMPO_RESET) {
        digitalWrite(PIN_M1, LOW);
        digitalWrite(PIN_LIGADA, LOW);
        finalizaIniciado = false;
        estado = IDLE; 
      }
      break;
  }
}
