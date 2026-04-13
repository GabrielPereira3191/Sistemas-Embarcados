const int botaoA = 2;
const int botaoB = 3;
const int led1   = 13;


bool ledAtivo        = false;
unsigned long tempoInicio = 0;
const unsigned long DURACAO = 5000; 

void setup() {
  pinMode(botaoA, INPUT_PULLUP);
  pinMode(botaoB, INPUT_PULLUP);
  pinMode(led1, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  bool pressionouA = digitalRead(botaoA) == LOW;
  bool pressionouB = digitalRead(botaoB) == LOW;

 
  if (pressionouA && !ledAtivo) {
    ledAtivo = true;
    tempoInicio = millis();
    digitalWrite(led1, HIGH);
    Serial.println("LED ligado — 5 segundos iniciados.");
  }

 
  if (pressionouB && ledAtivo) {
    ledAtivo = false;
    digitalWrite(led1, LOW);
    Serial.println("Cancelado pelo Botão B!");
  }

  
  if (ledAtivo && (millis() - tempoInicio >= DURACAO)) {
    ledAtivo = false;
    digitalWrite(led1, LOW);
    Serial.println("Tempo esgotado — LED apagado.");
  }
}