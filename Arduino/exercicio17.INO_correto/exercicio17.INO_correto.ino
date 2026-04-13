
const int potPin    = A0; 
const int motor     = 9;  
const int ledStatus = 10; 


const int botaoEmg  = 2;


bool emergencia = false;

void setup() {
  pinMode(motor,     OUTPUT);
  pinMode(ledStatus, OUTPUT);
  pinMode(botaoEmg,  INPUT_PULLUP);
  Serial.begin(9600);
  Serial.println("Sistema iniciado. Aguardando operação...");
}

void loop() {

  
  if (digitalRead(botaoEmg) == LOW && !emergencia) {
    delay(50); 
    if (digitalRead(botaoEmg) == LOW) {
      emergencia = true;
      analogWrite(motor, 0);      
      Serial.println("!!! EMERGÊNCIA ACIONADA — Motor parado !!!");
      while (digitalRead(botaoEmg) == LOW); 
    }
  }


  if (emergencia) {
    
    digitalWrite(ledStatus, HIGH);
    delay(200);
    digitalWrite(ledStatus, LOW);
    delay(200);

   
    if (digitalRead(botaoEmg) == LOW) {
      delay(50);
      if (digitalRead(botaoEmg) == LOW) {
        emergencia = false;
        digitalWrite(ledStatus, LOW);
        Serial.println(">>> Sistema REINICIADO. Operação normal.");
        while (digitalRead(botaoEmg) == LOW);
      }
    }
    return; 
  }

 
  int leitura   = analogRead(potPin);           
  int velocidade = map(leitura, 0, 1023, 0, 255); 

  analogWrite(motor, velocidade);
  digitalWrite(ledStatus, HIGH); 

  Serial.print("Velocidade PWM: ");
  Serial.print(velocidade);
  Serial.print("/255  |  Potenciômetro: ");
  Serial.println(leitura);

  delay(100);
}