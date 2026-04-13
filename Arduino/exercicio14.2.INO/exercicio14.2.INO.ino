const int botaoA  = 2;
const int botaoB  = 3;
const int maquina = 8; 
const int ledErro = 9; 

const unsigned long JANELA = 200; 

unsigned long tempoA = 0;
unsigned long tempoB = 0;
bool estadoA = false;
bool estadoB = false;

void setup() {
  pinMode(botaoA,  INPUT_PULLUP);
  pinMode(botaoB,  INPUT_PULLUP);
  pinMode(maquina, OUTPUT);
  pinMode(ledErro, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  bool leitA = digitalRead(botaoA) == LOW;
  bool leitB = digitalRead(botaoB) == LOW;

  
  if (leitA && !estadoA) { tempoA = millis(); estadoA = true; }
  if (!leitA)              estadoA = false;

 
  if (leitB && !estadoB) { tempoB = millis(); estadoB = true; }
  if (!leitB)              estadoB = false;

  if (estadoA && estadoB) {
    unsigned long diff = abs((long)tempoA - (long)tempoB);
    if (diff <= JANELA) {
      digitalWrite(maquina, HIGH);
      digitalWrite(ledErro, LOW);
      Serial.println("Máquina ACIONADA.");
    } else {
      digitalWrite(maquina, LOW);
      digitalWrite(ledErro, HIGH);
      Serial.println("ERRO: botões fora da janela de tempo.");
    }
  } else {
    digitalWrite(maquina, LOW);
    if (estadoA || estadoB) {
      digitalWrite(ledErro, HIGH); 
    } else {
      digitalWrite(ledErro, LOW);
    }
  }
}