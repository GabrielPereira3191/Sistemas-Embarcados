const int ntcPin = A0;

const int leds[] = {6, 7, 8, 9, 10};
const int N_LEDS = 5;

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
  for (int i = 0; i < N_LEDS; i++) pinMode(leds[i], OUTPUT);
  Serial.begin(9600);
}

void loop() {
  float temp   = lerTemperatura();

  
  int qtdLeds  = (int)((temp - TEMP_MIN) / (TEMP_MAX - TEMP_MIN) * N_LEDS);
  qtdLeds      = constrain(qtdLeds, 0, N_LEDS);

  for (int i = 0; i < N_LEDS; i++) {
    digitalWrite(leds[i], i < qtdLeds ? HIGH : LOW);
  }

  Serial.print("Temp: "); Serial.print(temp);
  Serial.print(" °C | LEDs acesos: "); Serial.println(qtdLeds);

  delay(300);
}