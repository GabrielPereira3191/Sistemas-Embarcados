const int led1 = 9;
const int led2 = 12;
const int botao1 = 2;
const int botao2 = 3;
const int analogPin = A0;

bool holding = false;
int valorcongelado = 0;

void setup() {
pinMode(led1, OUTPUT);
pinMode(led2, OUTPUT);
pinMode(botao1,  INPUT_PULLUP);
pinMode(botao2, INPUT_PULLUP);
Serial.begin(115200);
}
void loop(){
   if (digitalRead(botao1) == LOW) {
    delay(50);
    if(digitalRead(botao1) ==LOW) {
      valorcongelado = analogRead(analogPin) / 4;
      holding = true;
      digitalWrite(led2, HIGH);
      while(digitalRead(botao1) == LOW);
    }
  }
  if (digitalRead(botao2) == LOW){
    delay(50);
    if (digitalRead(botao2) == LOW){
      holding = false;
      digitalWrite(led2, LOW);
      while (digitalRead(botao2) == LOW);
    }
  }

 if (holding){
  analogWrite(led1, valorcongelado);
  } else {
    int val = analogRead(analogPin)/ 4;
    analogWrite(led1, val);

  }

} 



