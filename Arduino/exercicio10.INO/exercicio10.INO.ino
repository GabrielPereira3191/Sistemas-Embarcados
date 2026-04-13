const int botaoA = 2;
const int led1   = 12;
const int led2   = 13;

void setup() {
  pinMode(botaoA, INPUT_PULLUP);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
}

void loop() {
  
  if (digitalRead(botaoA) == LOW) {
    unsigned long tempoPress = millis();

    
    while (digitalRead(botaoA) == LOW);

    unsigned long duracao = millis() - tempoPress;

    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);

    if (duracao < 1000) {
      
      digitalWrite(led1, HIGH);
    } else if (duracao >= 2000) {
      
      digitalWrite(led2, HIGH);
    }
    
  }
}