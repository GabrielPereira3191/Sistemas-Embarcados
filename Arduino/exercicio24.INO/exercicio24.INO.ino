const int ntcPin    = A0;
const int ventilador = 9; 

const float R_FIXO   = 10000.0;
const float R_NOM    = 10000.0;
const float TEMP_NOM = 25.0;
const float BETA     = 3950.0;


const float TEMP_MIN = 20.0; 
const float TEMP_MAX = 60.0; 

float lerTemperatura() {
  int leitura  = analogRead(ntcPin);
  float resist = R_FIXO * (1023.0 / leitura - 1.0);
  float tempK  = 1.0 / ((1.0 / (TEMP_NOM + 273.15)) +
                 (1.0 / BETA) * log(resist / R_NOM));
  return tempK - 273.15;
}

void setup() {
  pinMode(ventilador, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  float temp = lerTemperatura();
  int pwm    = (int)((temp - TEMP_MIN) / (TEMP_MAX - TEMP_MIN) * 255.0);
  pwm        = constrain(pwm, 0, 255);

  analogWrite(ventilador, pwm);

  Serial.print("Temp: "); Serial.print(temp);
  Serial.print(" °C | PWM: "); Serial.println(pwm);

  delay(300);
}