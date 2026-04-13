#define inputHab  4
#define inputLiga 5

#define saidaA 10

void setup() {
  
  pinMode(inputHab, INPUT_PULLUP);
  pinMode(inputLiga, INPUT_PULLUP);

  pinMode(saidaA, OUTPUT);
}

void loop() {
  
  if (!digitalRead(inputHab)){  
    if (!digitalRead(inputLiga)){ 
      digitalWrite(saidaA, HIGH); 
    }
    else{
      digitalWrite(saidaA, LOW); 
    }
  }
  else{
    digitalWrite(saidaA, LOW);  
  }
}
