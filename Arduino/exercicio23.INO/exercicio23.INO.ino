const int ntcPin    = A0;
const int ledAquec  = 8; 


const float TEMP_LIGA   = 25.0; 
const float TEMP_DESLIGA = 30.0; 


const float R_FIXO   = 10000.0;
const float R_NOM    = 10000.0;
const float TEMP_NOM = 25.0;
const float BETA     = 3950.0;

bool aquecendo = false;

float lerTemperatura() {
  int leitura   = analogRead(ntcPin);
  float resist  = R_FIXO * (1023.0 / leitura - 1.0);
  float tempK   = 1.0 / ((1.0 / (TEMP_NOM + 273.15)) +
                  (1.0 / BETA) * log(resist / R_NOM));
  return tempK - 273.15;
}

void setup() {
  pinMode(ledAquec, OUTPUT);
  Serial.begin(9600);
  Serial.println("Controle térmico com histerese iniciado.");
  Serial.print("Liga abaixo de: ");  Serial.print(TEMP_LIGA);
  Serial.print("°C | Desliga acima de: "); Serial.print(TEMP_DESLIGA);
  Serial.println("°C");
}

void loop() {
  float temp = lerTemperatura();

  Serial.print("Temp: "); Serial.print(temp);
  Serial.print(" °C | Aquecedor: ");

  
  if (!aquecendo && temp < TEMP_LIGA) {
    aquecendo = true;
  } else if (aquecendo && temp > TEMP_DESLIGA) {
    aquecendo = false;
  }

  digitalWrite(ledAquec, aquecendo ? HIGH : LOW);
  Serial.println(aquecendo ? "LIGADO" : "DESLIGADO");

  delay(500);
}