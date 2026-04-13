const int ntcPin    = A0;
const int exaustor  = 9;  
const int ledMax    = 8;  

const float R_FIXO  = 10000.0;
const float R_NOM   = 10000.0;
const float TEMP_NOM = 25.0;
const float BETA    = 3950.0;

float lerTemperatura() {
  int leitura = analogRead(ntcPin);
  float resist = R_FIXO * (1023.0 / leitura - 1.0);
  float tempK  = 1.0 / ((1.0 / (TEMP_NOM + 273.15)) +
                 (1.0 / BETA) * log(resist / R_NOM));
  return tempK - 273.15;
}

void setup() {
  pinMode(exaustor, OUTPUT);
  pinMode(ledMax, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  float temp = lerTemperatura();

  Serial.print("Temp: "); Serial.print(temp); Serial.println(" °C");

  if (temp < 30.0) {
    
    analogWrite(exaustor, 51); 
    digitalWrite(ledMax, LOW);

  } else if (temp >= 30.0 && temp <= 60.0) {
    
    int pwm = map((int)temp, 30, 60, 51, 255);
    analogWrite(exaustor, pwm);
    digitalWrite(ledMax, LOW);

  } else {
   
    analogWrite(exaustor, 255);
    digitalWrite(ledMax, HIGH);
  }

  delay(500);
}