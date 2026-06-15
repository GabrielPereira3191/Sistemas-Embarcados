
const int PIN_NIVEL_ALTO   = 2;  
const int PIN_NIVEL_BAIXO  = 3;  
const int PIN_AUTO_MANUAL  = 4; 
const int PIN_LIGA         = 5;  
const int PIN_DESL         = 6;  
const int PIN_BOMBA        = 7;  

const unsigned long ATRASO = 10000UL; 

bool bombaLigada      = false;
bool esperandoLigar    = false;
bool esperandoDesligar = false;
unsigned long tLigar    = 0;
unsigned long tDesligar = 0;

bool nivelBaixoAnt = false;
bool nivelAltoAnt  = false;

void setup() {
  pinMode(PIN_NIVEL_ALTO,  INPUT_PULLUP);
  pinMode(PIN_NIVEL_BAIXO, INPUT_PULLUP);
  pinMode(PIN_AUTO_MANUAL, INPUT_PULLUP);
  pinMode(PIN_LIGA,        INPUT_PULLUP);
  pinMode(PIN_DESL,        INPUT_PULLUP);
  pinMode(PIN_BOMBA, OUTPUT);
  digitalWrite(PIN_BOMBA, LOW);
}

void loop() {
 
  bool modoAutomatico = (digitalRead(PIN_AUTO_MANUAL) == LOW);
  bool nivelAlto       = (digitalRead(PIN_NIVEL_ALTO)  == LOW);
  bool nivelBaixo      = (digitalRead(PIN_NIVEL_BAIXO) == LOW);
  bool botaoLiga       = (digitalRead(PIN_LIGA) == LOW);
  bool botaoDesl       = (digitalRead(PIN_DESL) == LOW);

  if (!modoAutomatico) {
   
    esperandoLigar    = false;
    esperandoDesligar = false;

    if (botaoLiga) bombaLigada = true;
    if (botaoDesl) bombaLigada = false;

  } else {
    

    
    if (nivelBaixo && !nivelBaixoAnt && !bombaLigada) {
      esperandoLigar = true;
      tLigar = millis();
    }

    
    if (nivelAlto && !nivelAltoAnt && bombaLigada) {
      esperandoDesligar = true;
      tDesligar = millis();
    }

    
    if (esperandoLigar && (millis() - tLigar >= ATRASO)) {
      bombaLigada = true;
      esperandoLigar = false;
    }

    
    if (esperandoDesligar && (millis() - tDesligar >= ATRASO)) {
      bombaLigada = false;
      esperandoDesligar = false;
    }

   
    if (!nivelBaixo) esperandoLigar = false;
    if (!nivelAlto)  esperandoDesligar = false;
  }

  nivelBaixoAnt = nivelBaixo;
  nivelAltoAnt  = nivelAlto;

  digitalWrite(PIN_BOMBA, bombaLigada ? HIGH : LOW);
}
