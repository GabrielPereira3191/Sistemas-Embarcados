const int potPin = A0;
const int led3   = 7;

void setup() {
  pinMode(led3, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  long soma = 0;

  for (int i = 0; i < 10; i++) {
    soma += analogRead(potPin);
    delay(10); 
  }

  float media = soma / 10.0;

  Serial.print("Média: ");
  Serial.println(media);

  if (media > 700) {
    digitalWrite(led3, HIGH);
  } else {
    digitalWrite(led3, LOW);
  }

  delay(200);
}