const int led1 = 6;
const int led2 = 9;
const int led3 = 10;
const int botao = 2;
const int botao2 = 3;
const int pinoTrigger = 13;
const int pinoEcho = 12;

void setup() {
  Serial.begin(9600); 
  pinMode(pinoTrigger, OUTPUT); 
  pinMode(pinoEcho, INPUT);     
}

void loop() {
  digitalWrite(pinoTrigger, LOW);
  delayMicroseconds(2);

  digitalWrite(pinoTrigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(pinoTrigger, LOW);


  long duracao = pulseIn(pinoEcho, HIGH);

  int distanciaCm = duracao * 0.034 / 2;

  Serial.print("Distancia: ");
  Serial.print(distanciaCm);
  Serial.println(" cm");

  delay(500); 
}
