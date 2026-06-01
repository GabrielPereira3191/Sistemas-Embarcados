int pin_sensor = A0;
const int valor_sensor = 8;
const int led1 = 9;
const int led2 = 10;
const int led3 = 11;

void setup() {
  pinMode(pin_sensor, INPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT)
  Serial.begin(115200);
}

void loop() {
 valor_sensor = analogRead(pin_sensor);
 float valor_tensao = (valor_tensao * 5.0)/ 1023
 Serial.print("Valor analogico =");
 Serial.println(valor_sensor);
 if (valor_tensao >= 4) {
  digitalWrite(pin_led1,1)
  digitalWrite(pint_led2,1)
  digitalWrite(pin_led3,1)
 }
  else if (valor_tensao >=3) {
  digitalWrite(pin_led1,0)
  digitalWrite(pint_led2,0)
  digitalWrite(pin_led3,1)
  }
  else if (valor_tensao >=2) {
   digitalWrite(pin_led1,0)
  digitalWrite(pint_led2,1)
  digitalWrite(pin_led3,0)
  } 
    else if (valor_tensao >=1 {
   digitalWrite(pin_led1,1)
  digitalWrite(pint_led2,0)
  digitalWrite(pin_led3,0)
    }
  else {
    digitalWrite(pin_led1,0)
  digitalWrite(pint_led2,0)
  digitalWrite(pin_led3,0)
  }
    

 }
}

