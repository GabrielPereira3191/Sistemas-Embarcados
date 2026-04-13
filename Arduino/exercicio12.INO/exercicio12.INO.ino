const int potPin = A0;
const int led    = 8;


const int NIVEL1 = 409;
const int NIVEL2 = 818;

void setup() {
  pinMode(led, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int valor = analogRead(potPin);

  Serial.print("Valor: "); Serial.println(valor);

  if (valor < NIVEL1) {
   
    digitalWrite(led, LOW);

  } else if (valor >= NIVEL1 && valor < NIVEL2) {
    
    digitalWrite(led, HIGH);
    delay(300);
    digitalWrite(led, LOW);
    delay(300);

  } else {
    
    digitalWrite(led, HIGH);
  }
}