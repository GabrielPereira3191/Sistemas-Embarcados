

const int PIN_START = 2;  
const int PIN_STOP  = 3;  
const int PIN_S1    = 4;  
const int PIN_S2    = 5;  
const int PIN_S3    = 6; 
const int PIN_S4    = 7;  

const int PIN_ESTEIRA   = 8; 
const int PIN_CIL_ALTAS = 9;  
const int PIN_CIL_BAIXAS= 10; 
const int PIN_LIGADA    = 11; 
const unsigned long TEMPO_ESTABILIZA = 2000UL; 

enum Estado { IDLE, AGUARDA_ESTABILIZAR, DESVIANDO, IDLE_FIM };
Estado estado = IDLE;

unsigned long tQueda = 0;
bool pecaAlta = false;

void setup() {
  pinMode(PIN_START, INPUT_PULLUP);
  pinMode(PIN_STOP,  INPUT_PULLUP);
  pinMode(PIN_S1, INPUT_PULLUP);
  pinMode(PIN_S2, INPUT_PULLUP);
  pinMode(PIN_S3, INPUT_PULLUP);
  pinMode(PIN_S4, INPUT_PULLUP);

  pinMode(PIN_ESTEIRA, OUTPUT);
  pinMode(PIN_CIL_ALTAS, OUTPUT);
  pinMode(PIN_CIL_BAIXAS, OUTPUT);
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
    digitalWrite(PIN_ESTEIRA, LOW);
    digitalWrite(PIN_CIL_ALTAS, LOW);
    digitalWrite(PIN_CIL_BAIXAS, LOW);
    digitalWrite(PIN_LIGADA, LOW);
    return;
  }

  switch (estado) {

    case IDLE:
      digitalWrite(PIN_ESTEIRA, LOW);
      digitalWrite(PIN_CIL_ALTAS, LOW);
      digitalWrite(PIN_CIL_BAIXAS, LOW);
      digitalWrite(PIN_LIGADA, LOW);
      if (start) {
       
        digitalWrite(PIN_LIGADA, HIGH);
        digitalWrite(PIN_ESTEIRA, HIGH);
        tQueda = millis();
        estado = AGUARDA_ESTABILIZAR;
      }
      break;

    case AGUARDA_ESTABILIZAR:
     
      if (millis() - tQueda >= TEMPO_ESTABILIZA) {
        
        pecaAlta = s3 && s4;
        if (pecaAlta) digitalWrite(PIN_CIL_ALTAS, HIGH);
        else          digitalWrite(PIN_CIL_BAIXAS, HIGH);
        estado = DESVIANDO;
      }
      break;

    case DESVIANDO:
     
      if ((pecaAlta && s1) || (!pecaAlta && s2)) {
        digitalWrite(PIN_ESTEIRA, LOW);
        digitalWrite(PIN_CIL_ALTAS, LOW);
        digitalWrite(PIN_CIL_BAIXAS, LOW);
        digitalWrite(PIN_LIGADA, LOW);
        estado = IDLE; 
      }
      break;

    default:
      estado = IDLE;
      break;
  }
}
