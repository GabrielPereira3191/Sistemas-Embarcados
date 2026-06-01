#include <Ultrasonic.h>
int led1 = 6;
int led2 = 9;
int led3 = 10;
int senBarreira = 7;
Ultrasonic ultrasonic(12, 13);
int distance;
const int botaoa = 2;
 

void setup() {
  Serial.begin(9600);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(botaoa, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(botaoa), desliga, CHANGE);
}

 

void loop() {

  distance = ultrasonic.read();
  int pwmled2 = map(distance, 0, 100, 0, 255);
  Serial.print("Distance in CM: ");
  Serial.println(distance);
  int leitura = digitalRead(senBarreira);
 
  if (distance < 20 && leitura == 0) {
    digitalWrite(led1, 1);
  } else {
    digitalWrite(led1, 0);
  }

  analogWrite(led2, pwmled2);

  if (leitura == 0) {
    digitalWrite(led3, 1);
  }

}

void desliga() {
  digitalWrite(led3, 0);
}
