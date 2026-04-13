const int ldrPin  = A0; 
const int led1    = 9; 
const int botaoA  = 2;  

const int NIVEL_ALVO = 700; 

void setup() {
  pinMode(led1,   OUTPUT);
  pinMode(botaoA, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {
  bool vazio      = digitalRead(botaoA) == HIGH; 
  int luzNatural  = analogRead(ldrPin); 

  int brilhoLED;

  if (vazio) {
    
    brilhoLED = 25; 
  } else {
    
    brilhoLED = NIVEL_ALVO - luzNatural;
    brilhoLED = constrain(brilhoLED, 0, 255);
  }

  analogWrite(led1, brilhoLED);

  Serial.print("Luz natural: "); Serial.print(luzNatural);
  Serial.print(" | LED PWM: ");  Serial.println(brilhoLED);

  delay(100);
}