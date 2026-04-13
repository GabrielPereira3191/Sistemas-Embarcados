const int botaoInc = 2;  
const int botaoDec = 3;  
const int motor    = 9;  

int velocidade = 0;       
const int PASSO = 25;     

bool ultimoInc = HIGH;
bool ultimoDec = HIGH;

void setup() {
  pinMode(botaoInc, INPUT_PULLUP);
  pinMode(botaoDec, INPUT_PULLUP);
  pinMode(motor,    OUTPUT);
  Serial.begin(9600);
  Serial.println("Velocidade inicial: 0");
}

void loop() {
  bool leitInc = digitalRead(botaoInc);
  bool leitDec = digitalRead(botaoDec);

 
  if (leitInc == LOW && ultimoInc == HIGH) {
    velocidade = constrain(velocidade + PASSO, 0, 255);
    Serial.print("Velocidade: "); Serial.println(velocidade);
    delay(50); 
  }

 
  if (leitDec == LOW && ultimoDec == HIGH) {
    velocidade = constrain(velocidade - PASSO, 0, 255);
    Serial.print("Velocidade: "); Serial.println(velocidade);
    delay(50); 
  }

  analogWrite(motor, velocidade);

  ultimoInc = leitInc;
  ultimoDec = leitDec;
}
