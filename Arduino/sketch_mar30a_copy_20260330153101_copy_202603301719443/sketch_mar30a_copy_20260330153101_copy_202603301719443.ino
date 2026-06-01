int pin_sensor = A0;
int valor_sensor = 8;
int led1 = 9
int led2 = 10
int led3 = 11

void setup() {
  pinMode(pin_sensor, INPUT);
  Serial.begin(115200);
}

void loop() {
 valor_sensor = analogRead(pin_sensor);
 Serial.print("Valor analogico =");
 Serial.println(valor_sensor);
 delay(200); 
}
