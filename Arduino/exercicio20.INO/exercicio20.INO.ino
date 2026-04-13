
    const int potPin = A0;
const int led1   = 8;  
const int led2   = 9;  
const int led3   = 10; 
const int led4   = 11; 



const int V180 = 737; 
const int V210 = 860;  
const int V230 = 942;  
const int V240 = 983;  

unsigned long tempoFora = 0;
bool foraDaFaixa        = false;
bool chaveFechada       = true;

void setup() {
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  digitalWrite(led4, HIGH); 
  Serial.begin(9600);
}

void apagarIndicadores() {
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
}

void loop() {
  int leitura = analogRead(potPin);
  float tensao = map(leitura, 0, 1023, 0, 250);

  Serial.print("Tensão: "); Serial.print(tensao); Serial.println(" V");

  apagarIndicadores();

  
  if (tensao >= 210 && tensao <= 230) {
    digitalWrite(led1, HIGH); 
  } else if (tensao < 210) {
    digitalWrite(led2, HIGH); 
  } else if (tensao > 230) {
    digitalWrite(led3, HIGH); 
  }

  
  bool faixaSegura = (tensao >= 180 && tensao <= 240);

  if (!faixaSegura) {
    if (!foraDaFaixa) {
      foraDaFaixa  = true;
      tempoFora    = millis();
    } else if (millis() - tempoFora >= 2000 && chaveFechada) {
      chaveFechada = false;
      digitalWrite(led4, LOW);
      Serial.println("!!! CHAVE GERAL DESLIGADA por segurança !!!");
    }
  } else {
    foraDaFaixa = false;
    if (!chaveFechada) {
      chaveFechada = true;
      digitalWrite(led4, HIGH);
      Serial.println(">>> Chave geral rearmada.");
    }
  }

  delay(100);
}