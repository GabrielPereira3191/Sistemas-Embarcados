const int potPin  = A0;
const int valvula = 8;  
const int alarme  = 9;  

bool valvulaBloqueada = false;

void setup() {
  pinMode(valvula, OUTPUT);
  pinMode(alarme, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int leitura = analogRead(potPin);
  int nivel   = map(leitura, 0, 1023, 0, 100); 

  Serial.print("Nível: "); Serial.print(nivel); Serial.println("%");

 
  if (nivel < 30) {
    valvulaBloqueada = false;
  }

  
  if (nivel >= 95) {
    valvulaBloqueada = true;
    digitalWrite(valvula, LOW);
    
    digitalWrite(alarme, HIGH);
    delay(200);
    digitalWrite(alarme, LOW);
    delay(200);
    return;
  }

  digitalWrite(alarme, LOW);

  if (!valvulaBloqueada && nivel < 80) {
    digitalWrite(valvula, HIGH); 
  } else {
    digitalWrite(valvula, LOW);  
  }

  delay(100);
}