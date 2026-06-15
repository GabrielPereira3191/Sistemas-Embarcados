
const int PIN_START = 2;
const int PIN_STOP  = 3;
const int PIN_FT    = 4;  
const int PIN_SP1   = 5;  
const int PIN_ST2   = 6;  
const int PIN_SR    = 7;  
const int PIN_SA    = 8;  

const int PIN_M1        = 9;  
const int PIN_MTAMP      = 10; 
const int PIN_CR_AVANCA  = 11; 
const int PIN_FC_ALARM   = 12; 
const int PIN_LIGADA     = 13; 

const unsigned long TEMPO_COROAMENTO = 2000UL; 
const int TOTAL_GARRAFAS = 24;

enum Estado {
  PARADO, RODANDO, COROANDO_AVANCO, COROANDO_ESPERA,
  COROANDO_RECUO, VERIFICA_P2, ALARME_FT, ALARME_FC
};
Estado estado = PARADO;

int contagem = 0;
unsigned long tCoroamento = 0;

void setup() {
  pinMode(PIN_START, INPUT_PULLUP);
  pinMode(PIN_STOP,  INPUT_PULLUP);
  pinMode(PIN_FT,    INPUT_PULLUP);
  pinMode(PIN_SP1,   INPUT_PULLUP);
  pinMode(PIN_ST2,   INPUT_PULLUP);
  pinMode(PIN_SR,    INPUT_PULLUP);
  pinMode(PIN_SA,    INPUT_PULLUP);

  pinMode(PIN_M1, OUTPUT);
  pinMode(PIN_MTAMP, OUTPUT);
  pinMode(PIN_CR_AVANCA, OUTPUT);
  pinMode(PIN_FC_ALARM, OUTPUT);
  pinMode(PIN_LIGADA, OUTPUT);

  digitalWrite(PIN_M1, LOW);
  digitalWrite(PIN_MTAMP, LOW);
  digitalWrite(PIN_CR_AVANCA, LOW);
  digitalWrite(PIN_FC_ALARM, LOW);
  digitalWrite(PIN_LIGADA, LOW);
}

void loop() {
  bool start = (digitalRead(PIN_START) == LOW);
  bool stop  = (digitalRead(PIN_STOP)  == LOW);
  bool faltaTampinha = (digitalRead(PIN_FT)  == LOW);
  bool garrafaP1     = (digitalRead(PIN_SP1) == LOW);
  bool tampaP2       = (digitalRead(PIN_ST2) == LOW); 
  bool cilRecuado    = (digitalRead(PIN_SR)  == LOW);
  bool cilAvancado   = (digitalRead(PIN_SA)  == LOW);

 
  if (stop) {
    estado = PARADO;
    digitalWrite(PIN_CR_AVANCA, LOW);
  }

  switch (estado) {

    case PARADO:
      digitalWrite(PIN_M1, LOW);
      digitalWrite(PIN_MTAMP, LOW);
      digitalWrite(PIN_LIGADA, LOW);
      if (start) {
        digitalWrite(PIN_FC_ALARM, LOW);
        contagem = 0;
        estado = RODANDO;
      }
      break;

    case RODANDO:
      digitalWrite(PIN_LIGADA, HIGH);
      digitalWrite(PIN_M1, HIGH);
      
      digitalWrite(PIN_MTAMP, faltaTampinha ? LOW : HIGH);

      if (faltaTampinha) {
        estado = ALARME_FT;
        break;
      }

      
      if (garrafaP1) {
        digitalWrite(PIN_M1, LOW);
        digitalWrite(PIN_CR_AVANCA, HIGH);
        estado = COROANDO_AVANCO;
      }
      break;

    case COROANDO_AVANCO:
      if (cilAvancado) {
        tCoroamento = millis();
        estado = COROANDO_ESPERA;
      }
      break;

    case COROANDO_ESPERA:
      
      if (millis() - tCoroamento >= TEMPO_COROAMENTO) {
        digitalWrite(PIN_CR_AVANCA, LOW);
        estado = COROANDO_RECUO;
      }
      break;

    case COROANDO_RECUO:
      if (cilRecuado) {
        contagem++;            
        estado = VERIFICA_P2;
      }
      break;

    case VERIFICA_P2:
      
      if (!tampaP2) {
        digitalWrite(PIN_FC_ALARM, HIGH);
        digitalWrite(PIN_M1, LOW);
        digitalWrite(PIN_MTAMP, LOW);
        estado = ALARME_FC;
      } else if (contagem >= TOTAL_GARRAFAS) {
        
        estado = PARADO;
      } else {
        estado = RODANDO;       
      }
      break;

    case ALARME_FT:
     
      digitalWrite(PIN_M1, LOW);
      digitalWrite(PIN_MTAMP, LOW);
      if (start && !faltaTampinha) {
        estado = RODANDO;
      }
      break;

    case ALARME_FC:
      
      if (start) {
        digitalWrite(PIN_FC_ALARM, LOW);
        estado = RODANDO;
      }
      break;
  }
}
