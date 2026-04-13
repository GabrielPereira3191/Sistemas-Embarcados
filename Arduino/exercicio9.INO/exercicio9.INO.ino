const int potPin = A0;
const int led1   = 9;  // PWM
const int led2   = 10; // PWM

void setup() {
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
}

void loop() {
  int valor = analogRead(potPin); 

  if (valor < 512) {
    
    int brilho = map(valor, 511, 0, 0, 255);
    analogWrite(led1, brilho);
    analogWrite(led2, 0);
  } else if (valor > 512) {
    
    int brilho = map(valor, 513, 1023, 0, 255);
    analogWrite(led1, 0);
    analogWrite(led2, brilho);
  } else {
   
    analogWrite(led1, 0);
    analogWrite(led2, 0);
  }

  delay(20);
}