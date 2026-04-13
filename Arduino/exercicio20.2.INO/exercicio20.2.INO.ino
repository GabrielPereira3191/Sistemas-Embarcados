
const int potNivel = A0; 
const int ntcPin   = A1; 
const int botao    = 2;  


const int led1Valvula = 7;  
const int led2Aquec   = 9;  
const int led3Alarme  = 8;  


const int NIVEL_BAIXO = 300; 
const int NIVEL_ALTO  = 750; 

const float TEMP_BAIXA = 25.0; 
const float TEMP_ALTA  = 50.0; 


const float R_FIXO   = 10000.0;
const float R_NOM    = 10000.0;
const float TEMP_NOM = 25.0;
const float BETA     = 3950.0;

float lerTemperatura() {
  int leitura  = analogRead(ntcPin);
  float resist = R_FIXO * (1023.0 / leitura - 1.0);
  float tempK  = 1.0 / ((1.0 / (TEMP_NOM + 273.15)) +
                 (1.0 / BETA) * log(resist / R_NOM));
  return tempK - 273.15;
}

void desligarTudo() {
  digitalWrite(led1Valvula, LOW);
  analogWrite(led2Aquec,    0);
  digitalWrite(led3Alarme,  LOW);
}

void setup() {
  pinMode(botao,       INPUT_PULLUP);
  pinMode(led1Valvula, OUTPUT);
  pinMode(led2Aquec,   OUTPUT);
  pinMode(led3Alarme,  OUTPUT);
  Serial.begin(9600);
  Serial.println("Sistema de tanque pronto.");
}

void loop() {
  
  bool habilitado = digitalRead(botao) == LOW;

  if (!habilitado) {
    desligarTudo();
    Serial.println("Sistema DESABILITADO.");
    delay(300);
    return;
  }


  int   nivel = analogRead(potNivel);
  float temp  = lerTemperatura();
  int   nivelPct = map(nivel, 0, 1023, 0, 100);

  Serial.print("Nível: "); Serial.print(nivelPct);
  Serial.print("% | Temp: "); Serial.print(temp);
  Serial.println(" °C");

  if (nivel < NIVEL_BAIXO) {
    digitalWrite(led1Valvula, HIGH);
    Serial.println("Válvula: ABERTA");
  } else if (nivel >= NIVEL_ALTO) {
    digitalWrite(led1Valvula, LOW);  /
    Serial.println("Válvula: FECHADA");
  }

  
  if (temp > TEMP_ALTA) {
    
    analogWrite(led2Aquec,   0);
    digitalWrite(led3Alarme, HIGH);
    Serial.println("ALARME: temperatura alta!");

  } else if (temp < TEMP_BAIXA) {
    
    analogWrite(led2Aquec,   200); 
    digitalWrite(led3Alarme, LOW);
    Serial.println("Aquecedor: LIGADO");

  } else {
    
    analogWrite(led2Aquec,   0);
    digitalWrite(led3Alarme, LOW);
    Serial.println("Sistema: NORMAL");
  }

  delay(300);
}
