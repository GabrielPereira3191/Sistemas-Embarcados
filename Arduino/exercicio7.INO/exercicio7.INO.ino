#define saidaLed   9

const long int intervalo = 200;
int tempoAtual = 0, tempoAnterior = 0;
int controleLed = 0;
long int saidaAnalogica = 0, entradaAnalogica = 0;
float tempoLed = 0;
bool auxPulso = 0;

void setup() {
 
  pinMode(saidaLed, OUTPUT);
  Serial.begin(9600);
}

void loop() {
 
  entradaAnalogica = analogRead(A0);
  tempoLed = ((1.99*entradaAnalogica) - 2138.77)/-1023;

  tempoAtual = millis(); 

  if (tempoAtual - tempoAnterior >= ((int)tempoLed*1000)) {
    tempoAnterior = tempoAtual; 
    digitalWrite(saidaLed, !digitalRead(saidaLed));
  }
 
}
