const int botao1 = 2;
const int botao2 = 3;
const int leds[] = {8, 9, 10, 11}; 

bool sequenciaAtiva = false;

void setup() {
  pinMode(botao1, INPUT_PULLUP);
  pinMode(botao2, INPUT_PULLUP);
  for (int i = 0; i < 4; i++) {
    pinMode(leds[i], OUTPUT);
  }
}

void loop() {
  
  if (digitalRead(botao1) == LOW && !sequenciaAtiva) {
    sequenciaAtiva = true;
    for (int i = 0; i < 4; i++) {
      digitalWrite(leds[i], HIGH);
      
      unsigned long t = millis();
      while (millis() - t < 1000) {
        if (digitalRead(botao2) == LOW) {
          apagarTodos();
          sequenciaAtiva = false;
          return;
        }
      }
    }
  }

  
  if (digitalRead(botao2) == LOW) {
    apagarTodos();
    sequenciaAtiva = false;
    delay(300); 
  }
}

void apagarTodos() {
  for (int i = 0; i < 4; i++) {
    digitalWrite(leds[i], LOW);
  }
}