const int potPin   = A0;
const int ledNorm  = 7; 
const int ledAlarm = 8;  
const int LIMITE_CRITICO = 800; 

void setup() {
  pinMode(ledNorm,  OUTPUT);
  pinMode(ledAlarm, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int leitura = analogRead(potPin);

  Serial.print("Leitura: "); Serial.println(leitura);

  if (leitura > LIMITE_CRITICO) {
   
    digitalWrite(ledNorm, LOW);
    digitalWrite(ledAlarm, HIGH); delay(80);
    digitalWrite(ledAlarm, LOW);  delay(80);
    Serial.println("!!! ALERTA CRÍTICO !!!");
  } else {
   
    digitalWrite(ledNorm,  HIGH);
    digitalWrite(ledAlarm, LOW);
    delay(100);
  }
}