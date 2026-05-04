const int ledPin  = 13;
const long INTERVALO = 500; 

void setup() {
  pinMode(ledPin, OUTPUT);
}

void loop() {

  for (int i = 0; i < 20; i++) {

    digitalWrite(ledPin, HIGH);
    unsigned long inicio = millis();
    while (millis() - inicio < INTERVALO) {
    }

    digitalWrite(ledPin, LOW);
    inicio = millis();
    while (millis() - inicio < INTERVALO) {
    }

  } 
  while (true) { }

}