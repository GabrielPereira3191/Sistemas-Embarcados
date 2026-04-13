const int sensorPresenca = 2; // Botão A
const int esteira        = 8; // LED 1

bool esteiraAtiva        = false;
unsigned long ultimaDeteccao = 0;
const unsigned long TIMEOUT = 3000; 

void setup() {
  pinMode(sensorPresenca, INPUT_PULLUP);
  pinMode(esteira, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  bool caixaDetectada = digitalRead(sensorPresenca) == LOW;

  if (caixaDetectada) {
    ultimaDeteccao = millis();
    if (!esteiraAtiva) {
      esteiraAtiva = true;
      Serial.println("Caixa detectada — esteira ligada.");
    }
  }

  
  if (esteiraAtiva && (millis() - ultimaDeteccao >= TIMEOUT)) {
    esteiraAtiva = false;
    Serial.println("Sem caixas — esteira parada.");
  }

  digitalWrite(esteira, esteiraAtiva ? HIGH : LOW);
}