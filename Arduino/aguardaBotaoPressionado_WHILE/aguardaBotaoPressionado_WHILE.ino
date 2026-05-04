const int botaoPin = 2;
const int ledPin   = 13;  
const int ledStatus = 12; 

unsigned long ultimoTempo = 0;
bool estadoStatus = false;

void setup() {
  pinMode(botaoPin, INPUT_PULLUP);
  pinMode(ledPin,   OUTPUT);
  pinMode(ledStatus, OUTPUT);
  Serial.begin(9600);
  Serial.println("Aguardando botão...");
}

void loop() {

  while (digitalRead(botaoPin) == HIGH) {

    unsigned long agora = millis();
    if (agora - ultimoTempo >= 300) {
      ultimoTempo = agora;
      estadoStatus = !estadoStatus;
      digitalWrite(ledStatus, estadoStatus);
    }

  } 

  digitalWrite(ledStatus, LOW);   
  digitalWrite(ledPin, HIGH);    
  Serial.println("Botão pressionado!");

}