const int botaoA = 2;
const int led1   = 8; 
const int led2   = 9;  
const int led3   = 10; 
const int led4   = 11;


bool cicloAtivo = false;

void setup() {
  pinMode(botaoA, INPUT_PULLUP);
  pinMode(led1,   OUTPUT);
  pinMode(led2,   OUTPUT);
  pinMode(led3,   OUTPUT);
  pinMode(led4,   OUTPUT);
  Serial.begin(9600);
  Serial.println("Sistema pronto. Pressione Botão A para iniciar.");
}


void apagarTodos() {
  digitalWrite(led1, LOW);
  analogWrite(led2,  0);
  analogWrite(led3,  0);
  digitalWrite(led4, LOW);
}


void etapaEnchimento() {
  Serial.println(">>> Etapa 1: ENCHIMENTO (4s)");
  digitalWrite(led1, HIGH);

  unsigned long inicio = millis();
  while (millis() - inicio < 4000); 

  digitalWrite(led1, LOW);
}


void etapaLavagem() {
  Serial.println(">>> Etapa 2: LAVAGEM (8s)");

  unsigned long inicio = millis();
  while (millis() - inicio < 8000) {
    
    analogWrite(led2, 127); 
    analogWrite(led3, 0);
    delay(400);

    
    analogWrite(led2, 0);
    analogWrite(led3, 127); 
    delay(400);
  }

  analogWrite(led2, 0);
  analogWrite(led3, 0);
}


void etapaDrenagem() {
  Serial.println(">>> Etapa 3: DRENAGEM (4s)");
  digitalWrite(led4, HIGH);

  unsigned long inicio = millis();
  while (millis() - inicio < 4000); 

  digitalWrite(led4, LOW);
}

void loop() {

  
  if (!cicloAtivo && digitalRead(botaoA) == LOW) {
    delay(50); 
    if (digitalRead(botaoA) == LOW) {
      cicloAtivo = true;
      apagarTodos();
      Serial.println("=== CICLO INICIADO ===");

      
      etapaEnchimento();
      etapaLavagem();
      etapaDrenagem();

      cicloAtivo = false;
      Serial.println("=== CICLO CONCLUÍDO. Pressione Botão A para novo ciclo. ===");

      while (digitalRead(botaoA) == LOW); 
    }
  }
}