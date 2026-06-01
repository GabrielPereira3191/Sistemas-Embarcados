const int analogPin = A0;
const int led = 9;

void setup() {
  pinMode(led, OUTPUT);
  Serial.begin(115200);
}

void loop(){
  int valor = analogRead(analogPin);
  Serial.println(valor);
  valor = map(valor, 0, 1023, 0, 255);
  analogWrite(led, valor);
}