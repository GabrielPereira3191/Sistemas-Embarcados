const int leds[] = {8, 9, 10, 11, 12};
const int NUM_LEDS = 5;
int ledAtual = 0;
unsigned long ultimoTempo = 0;
const long INTERVALO = 400;

void setup() {
  for (int i = 0; i < NUM_LEDS; i++) {
    pinMode(leds[i], OUTPUT);
  }
}

void loop() {
  unsigned long agora = millis();
  if (agora - ultimoTempo >= INTERVALO) {
    ultimoTempo = agora;

    for (int i = 0; i < NUM_LEDS; i++)
      digitalWrite(leds[i], LOW);

    digitalWrite(leds[ledAtual], HIGH);
    ledAtual = (ledAtual + 1) % NUM_LEDS; 
  }
}