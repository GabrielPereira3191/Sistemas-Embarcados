const int botaoA  = 2;
const int atuador = 8; 

bool cicloAtivo       = false;
unsigned long tempoInicio = 0;
const unsigned long DURACAO = 5000; 

bool ultimoEstado = HIGH;

void setup() {
  pinMode(botaoA,  INPUT_PULLUP);
  pinMode(atuador, OUTPUT);
  Serial.begin(9600);
  Serial.println("Sistema pronto. Pressione Botão A para iniciar ciclo.");
}

void loop() {
  bool leitura = digitalRead(botaoA);

  
  if (leitura == LOW && ultimoEstado == HIGH) {
    if (!cicloAtivo) {
      cicloAtivo   = true;
      tempoInicio  = millis();
      digitalWrite(atuador, HIGH);
      Serial.println(">>> Ciclo INICIADO — atuador ligado por 5s.");
    } else {
      Serial.println("Ciclo em andamento. Aguarde...");
    }
    delay(50); 
  }

  ultimoEstado = leitura;

  
  if (cicloAtivo && (millis() - tempoInicio >= DURACAO)) {
    cicloAtivo = false;
    digitalWrite(atuador, LOW);
    Serial.println(">>> Ciclo CONCLUÍDO. Pronto para reinicialização.");
  }

  
  if (cicloAtivo) {
    unsigned long restante = DURACAO - (millis() - tempoInicio);
    Serial.print("Restante: ");
    Serial.print(restante / 1000.0, 1);
    Serial.println("s");
    delay(200);
  }
}