const int potPin   = A0;
const int ledBaixo = 7;  
const int ledMedio = 8;  
const int ledAlto  = 9;  
const int ledCrit  = 10; 

void setup() {
  pinMode(ledBaixo, OUTPUT);
  pinMode(ledMedio, OUTPUT);
  pinMode(ledAlto,  OUTPUT);
  pinMode(ledCrit,  OUTPUT);
  Serial.begin(9600);
}

void apagarTodos() {
  digitalWrite(ledBaixo, LOW);
  digitalWrite(ledMedio, LOW);
  digitalWrite(ledAlto,  LOW);
  digitalWrite(ledCrit,  LOW);
}

void loop() {
  int leitura = analogRead(potPin);
  int nivel   = map(leitura, 0, 1023, 0, 100); 

  Serial.print("Nível: "); Serial.print(nivel); Serial.println("%");

  apagarTodos();

  if (nivel <= 10 || nivel >= 90) {
    /
    digitalWrite(ledCrit, HIGH); delay(150);
    digitalWrite(ledCrit, LOW);  delay(150);
  } else if (nivel <= 40) {
    digitalWrite(ledBaixo, HIGH);
  } else if (nivel <= 70) {
    digitalWrite(ledMedio, HIGH);
  } else {
    digitalWrite(ledAlto,  HIGH);
  }

  delay(100);
}