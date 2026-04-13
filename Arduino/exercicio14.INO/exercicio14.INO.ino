const int botaoA  = 2;
const int botaoB  = 3;
const int prensa  = 8; 
const int ledErro = 9;  

unsigned long tempoA = 0;
unsigned long tempoB = 0;
bool estadoA = false;
bool estadoB = false;

const unsigned long TOLERANCIA = 500; 

void setup() {
  pinMode(botaoA, INPUT_PULLUP);
  pinMode(botaoB, INPUT_PULLUP);
  pinMode(prensa, OUTPUT);
  pinMode(ledErro, OUTPUT);
}

void loop() {
  bool leituraA = digitalRead(botaoA) == LOW;
  bool leituraB = digitalRead(botaoB) == LOW;

  
  if (leituraA && !estadoA) {
    estadoA = true;
    tempoA  = millis();
  }
  if (!leituraA) estadoA = false;

  
  if (leituraB && !estadoB) {
    estadoB = true;
    tempoB  = millis();
  }
  if (!leituraB) estadoB = false;

 
  if (estadoA && estadoB) {
    unsigned long diferenca = abs((long)tempoA - (long)tempoB);

    if (diferenca <= TOLERANCIA) {
     
      digitalWrite(prensa, HIGH);
      digitalWrite(ledErro, LOW);
    } else {
      
      digitalWrite(prensa, LOW);
      digitalWrite(ledErro, HIGH);
    }
  } else {
    digitalWrite(prensa, LOW);
    
    if (estadoA || estadoB) {
      digitalWrite(ledErro, HIGH);
    } else {
      digitalWrite(ledErro, LOW);
    }
  }
}