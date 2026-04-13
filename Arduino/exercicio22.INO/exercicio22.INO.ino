const int botaoA  = 2;
const int led1    = 8;  
const int led2    = 9;  
const int led3    = 10; 
const int potPin  = A0; 

bool cicloAtivo = false;

void setup() {
  pinMode(botaoA, INPUT_PULLUP);
  pinMode(led1,   OUTPUT);
  pinMode(led2,   OUTPUT);
  pinMode(led3,   OUTPUT);
  Serial.begin(9600);
  Serial.println("Solda pronta. Posicione a peça e pressione Botão A.");
}

void loop() {
  if (!cicloAtivo && digitalRead(botaoA) == LOW) {
    delay(50);
    if (digitalRead(botaoA) == LOW) {
      cicloAtivo = true;
      while (digitalRead(botaoA) == LOW);

      
      Serial.println("Estabilizando...");
      delay(800);

      
      Serial.println("Atuador de pressão ATIVO.");
      digitalWrite(led1, HIGH);

      
      delay(200);
      int potencia = map(analogRead(potPin), 0, 1023, 0, 255);
      Serial.print("Corrente de solda — PWM: "); Serial.println(potencia);
      analogWrite(led2, potencia);
      delay(1500);

      
      analogWrite(led2, 0);
      Serial.println("Resfriando sob pressão...");
      delay(500);
      digitalWrite(led1, LOW);

      
      Serial.println("Peça liberada — PRONTO.");
      digitalWrite(led3, HIGH);
      delay(2000);
      digitalWrite(led3, LOW);

      cicloAtivo = false;
      Serial.println("Sistema livre para nova solda.");
    }
  }
}