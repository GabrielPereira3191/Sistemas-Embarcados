const int sensores[] = {A0, A1, A2, A3};
const int NUM_SENS = 4;
unsigned long ultimaLeitura = 0;
const long INTERVALO = 500;

void setup() {
  Serial.begin(9600);
  Serial.println("Leitura de sensores:");
}

void loop() {
  unsigned long agora = millis();
  if (agora - ultimaLeitura >= INTERVALO) {
    ultimaLeitura = agora;

    for (int i = 0; i < NUM_SENS; i++) {
      int valor = analogRead(sensores[i]);
      Serial.print("A");
      Serial.print(i);
      Serial.print(": ");
      Serial.print(valor);
      if (i < NUM_SENS - 1) Serial.print("  |  ");
    }
    Serial.println();
  }
}