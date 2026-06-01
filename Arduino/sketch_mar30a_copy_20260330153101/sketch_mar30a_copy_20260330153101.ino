const int pin_botaoA = 2;
const int pin_botaoB = 3;
const int pin_ledA = 8;
const int pin_ledB = 9;
const int pin_ledC = 10;
const int pin_ledD = 11;
int estado_ledA = LOW;
int estado_ledB = LOW;
int estado_ledC = LOW;
int estado_ledD = LOW;
int estado_botaoA;
int estado_botaoB;
int ultimo_estado_botaoA = HIGH;
int ultimo_estado_botaoB = HIGH;
unsigned long tempo_debounceA = 0;
unsigned long tempo_debounceB = 0;
unsigned long atraso = 300;

void setup() {
  pinMode(pin_botaoA, INPUT_PULLUP);
  pinMode(pin_botaoB, INPUT_PULLUP);
  pinMode(pin_ledA, OUTPUT);
  pinMode(pin_ledB, OUTPUT);
  pinMode(pin_ledC, OUTPUT);
  pinMode(pin_ledD, OUTPUT);
  digitalWrite(pin_ledA, estado_ledA);
  digitalWrite(pin_ledB, estado_ledB);
  digitalWrite(pin_ledC, estado_ledC);
  digitalWrite(pin_ledD, estado_ledD);
}
  

void loop() {
  int leituraA = digitalRead(pin_botaoA);
  if (leituraA != ultimo_estado_botaoA){
    tempo_debounceA = millis();
  }
  {
    if(leituraA != estado_botaoA) {
      estado_botaoA = leituraA;
      if(estado_botaoA == LOW) {
        estado_ledA = !estado_ledA;
         estado_ledC = !estado_ledC;
      ((millis() - tempo_debounceA)  > atraso);
      
       
         
         
  
      
      }
    }
  }

  digitalWrite(pin_ledA, estado_ledA);
  digitalWrite(pin_ledC, estado_ledC);
  ultimo_estado_botaoA = leituraA;

}

