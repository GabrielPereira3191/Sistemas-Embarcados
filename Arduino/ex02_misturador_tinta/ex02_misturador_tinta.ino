
const int PIN_START1 = 2;  
const int PIN_START2 = 3;  
const int PIN_STOP1  = 4;  
const int PIN_STOP2  = 5;  
const int PIN_HIGH   = 6;  
const int PIN_LOW    = 7; 

const int PIN_PUMP1      = 8; 
const int PIN_PUMP2      = 9;  
const int PIN_MIXER      = 10;
const int PIN_STEAM      = 11; 
const int PIN_DRAINVALVE = 12; 
const int PIN_DRAINPUMP  = 13; 

const unsigned long TEMPO_MISTURA = 10000UL; 

enum Estado { ENCHENDO, MISTURANDO, DRENANDO };
Estado estado = ENCHENDO;

bool pump1Latch = false;
bool pump2Latch = false;
unsigned long tMistura = 0;
unsigned int contadorCiclos = 0;

void setup() {
  pinMode(PIN_START1, INPUT_PULLUP);
  pinMode(PIN_START2, INPUT_PULLUP);
  pinMode(PIN_STOP1,  INPUT_PULLUP);
  pinMode(PIN_STOP2,  INPUT_PULLUP);
  pinMode(PIN_HIGH,   INPUT_PULLUP);
  pinMode(PIN_LOW,    INPUT_PULLUP);

  pinMode(PIN_PUMP1, OUTPUT);
  pinMode(PIN_PUMP2, OUTPUT);
  pinMode(PIN_MIXER, OUTPUT);
  pinMode(PIN_STEAM, OUTPUT);
  pinMode(PIN_DRAINVALVE, OUTPUT);
  pinMode(PIN_DRAINPUMP,  OUTPUT);
}

void loop() {
  bool start1 = (digitalRead(PIN_START1) == LOW);
  bool start2 = (digitalRead(PIN_START2) == LOW);
  bool stop1  = (digitalRead(PIN_STOP1)  == LOW); 
  bool stop2  = (digitalRead(PIN_STOP2)  == LOW);
  bool nivelAlto  = (digitalRead(PIN_HIGH) == LOW);
  bool nivelBaixo = (digitalRead(PIN_LOW)  == LOW);

  switch (estado) {

    case ENCHENDO:
      
      if (start1 && !nivelAlto) pump1Latch = true;
      if (stop1 || nivelAlto)   pump1Latch = false;

     
      if (start2 && !nivelAlto) pump2Latch = true;
      if (stop2 || nivelAlto)   pump2Latch = false;

      digitalWrite(PIN_PUMP1, pump1Latch ? HIGH : LOW);
      digitalWrite(PIN_PUMP2, pump2Latch ? HIGH : LOW);

      
      if (nivelAlto) {
        digitalWrite(PIN_PUMP1, LOW);
        digitalWrite(PIN_PUMP2, LOW);
        pump1Latch = false;
        pump2Latch = false;
        digitalWrite(PIN_MIXER, HIGH);
        digitalWrite(PIN_STEAM, HIGH);
        tMistura = millis();
        estado = MISTURANDO;
      }
      break;

    case MISTURANDO:
      if (millis() - tMistura >= TEMPO_MISTURA) {
        digitalWrite(PIN_MIXER, LOW);
        digitalWrite(PIN_STEAM, LOW);
        digitalWrite(PIN_DRAINVALVE, HIGH);
        digitalWrite(PIN_DRAINPUMP,  HIGH);
        estado = DRENANDO;
      }
      break;

    case DRENANDO:
      if (nivelBaixo) {
        digitalWrite(PIN_DRAINVALVE, LOW);
        digitalWrite(PIN_DRAINPUMP,  LOW);
        contadorCiclos++;    
        estado = ENCHENDO;
      }
      break;
  }
}
