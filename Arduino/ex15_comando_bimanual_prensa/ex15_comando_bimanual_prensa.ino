

const int PIN_CMD_A = 2;  
const int PIN_CMD_B = 3;  
const int PIN_R     = 4;  

const unsigned long TEMPO_LIMITE = 3000UL; 

bool prensaAtiva = false;

unsigned long tPressA = 0;
unsigned long tPressB = 0;

bool aAnt = false;
bool bAnt = false;

void setup() {
  pinMode(PIN_CMD_A, INPUT_PULLUP);
  pinMode(PIN_CMD_B, INPUT_PULLUP);
  pinMode(PIN_R, OUTPUT);
  digitalWrite(PIN_R, LOW);
}

void loop() {
  bool a = (digitalRead(PIN_CMD_A) == LOW); 
  bool b = (digitalRead(PIN_CMD_B) == LOW);

 
  if (a && !aAnt) tPressA = millis();
  if (b && !bAnt) tPressB = millis();

  if (prensaAtiva) {
   
    if (!a || !b) {
      prensaAtiva = false;
      digitalWrite(PIN_R, LOW);
      tPressA = 0;
      tPressB = 0;
    }
  } else {
    if (a && b) {
      unsigned long diff = (tPressA > tPressB) ? (tPressA - tPressB)
                                               : (tPressB - tPressA);
      if (diff <= TEMPO_LIMITE) {
        prensaAtiva = true;
        digitalWrite(PIN_R, HIGH);
      } else {
      
        if (!a || !b) { tPressA = 0; tPressB = 0; }
      }
    } else {
      if (a && !b && (millis() - tPressA > TEMPO_LIMITE)) {  
      }
      if (b && !a && (millis() - tPressB > TEMPO_LIMITE)) {
      }
    }
  }

  aAnt = a;
  bAnt = b;
}
