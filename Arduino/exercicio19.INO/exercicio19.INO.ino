const int ntcPin = A0;
const int led4   = 8;


const float R_FIXO     = 10000.0; 
const float R_NOM      = 10000.0; 
const float TEMP_NOM   = 25.0;   
const float BETA       = 3950.0;  
const float TEMP_LIMITE = 40.0;  

void setup() {
  pinMode(led4, OUTPUT);
  Serial.begin(9600); 
}

void loop() {
  /
  int leitura = analogRead(ntcPin);

 
  float resistencia = R_FIXO * (1023.0 / leitura - 1.0);

  
  float tempKelvin = 1.0 / (
    (1.0 / (TEMP_NOM + 273.15)) +
    (1.0 / BETA) * log(resistencia / R_NOM)
  );
  float tempCelsius = tempKelvin - 273.15;

  Serial.print("Temperatura: ");
  Serial.print(tempCelsius);
  Serial.println(" °C");

  
  if (tempCelsius > TEMP_LIMITE) {
   
    digitalWrite(led4, HIGH);
    delay(100);
    digitalWrite(led4, LOW);
    delay(100);
  } else {
    digitalWrite(led4, LOW); 
  }
}