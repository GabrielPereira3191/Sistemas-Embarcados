
const int PIN_START = 2;  
const int PIN_STOP  = 3;  
const int PIN_S2    = 4;
const int PIN_S3    = 5; 

const int PIN_M1     = 6;  
const int PIN_M2     = 7; 
const int PIN_C1     = 8;  
const int PIN_LIGADA = 9;  

const unsigned long TEMPO_AVANCO  = 1000UL;
const unsigned long TEMPO_RECUO   = 1000UL; 
const int TOTAL_CORTES = 5;

enum Estado { IDLE, ALIMENTA_CHAPA, CORTE_AVANCA, CORTE_RECUA, AVANCA_CAIXA };
Estado estado = IDLE;

unsigned long tCilindro = 0;
int contadorCortes = 0;

void setup() {
  pinMode(PIN_START, INPUT_PULLUP);
  pinMode(PIN_STOP,  INPUT_PULLUP);
  pinMode(PIN_S2, INPUT_PULLUP);
  pinMode(PIN_S3, INPUT_PULLUP);

  pinMode(PIN_M1, OUTPUT);
  pinMode(PIN_M2, OUTPUT);
  pinMode(PIN_C1, OUTPUT);
  pinMode(PIN_LIGADA, OUTPUT);
}

void loop() {
  bool start = (digitalRead(PIN_START) == LOW);
  bool stop  = (digitalRead(PIN_STOP)  == LOW);
  bool s2 = (digitalRead(PIN_S2) == LOW);
  bool s3 = (digitalRead(PIN_S3) == LOW);

  if (stop) {
    estado = IDLE;
    digitalWrite(PIN_M1, LOW);
    digitalWrite(PIN_M2, LOW);
    digitalWrite(PIN_C1, LOW);
    digitalWrite(PIN_LIGADA, LOW);
    return;
  }

  switch (estado) {

    case IDLE:
      if (start) {
        digitalWrite(PIN_LIGADA, HIGH);
        contadorCortes = 0;
        digitalWrite(PIN_M1, HIGH);
        digitalWrite(PIN_M2, HIGH); 
        estado = ALIMENTA_CHAPA;
      }
      break;

    case ALIMENTA_CHAPA:
     
      if (s2) {
        digitalWrite(PIN_M1, LOW);
        digitalWrite(PIN_C1, HIGH); 
        tCilindro = millis();
        estado = CORTE_AVANCA;
      }
      break;

    case CORTE_AVANCA:
      if (millis() - tCilindro >= TEMPO_AVANCO) {
        digitalWrite(PIN_C1, LOW); 
        tCilindro = millis();
        estado = CORTE_RECUA;
      }
      break;

    case CORTE_RECUA:
      if (millis() - tCilindro >= TEMPO_RECUO) {
        contadorCortes++;
        if (contadorCortes < TOTAL_CORTES) {
          
          digitalWrite(PIN_M1, HIGH);
          estado = ALIMENTA_CHAPA;
        } else {
          
          estado = AVANCA_CAIXA;
        }
      }
      break;

    case AVANCA_CAIXA:
     
      if (s3) {
        digitalWrite(PIN_M2, LOW);
        digitalWrite(PIN_LIGADA, LOW);
        estado = IDLE; 
      }
      break;
  }
}
