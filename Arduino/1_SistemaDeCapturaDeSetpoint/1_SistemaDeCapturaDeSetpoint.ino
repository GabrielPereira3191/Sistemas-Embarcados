const int led1 = 9;
const int led4 = 12;
const int botao1 = 2;
const int analogPin = A0;
const int analogPin2 = A1;

bool bombaligada = false;
bool alarme = false;
unsigned long piscartimer = 0;
bool piscarestado = false;

float lernivel() {
 return analogRead(analogPin) * (100.0 / 1023.0);
}
float lertemperatura() {
 return analogRead(analogPin2 ) * (100.0 / 1023.0);
}

void setup() {
pinMode(led1, OUTPUT);
pinMode(led4, OUTPUT);
pinMode(botao1,  INPUT_PULLUP);
}

void loop(){
float nivel = lernivel();
float temp = lertemperatura();

if (temp  > 80.0 && !alarme) {
  alarme = true;
  bombaligada = false;
  digitalWrite(led1, LOW);
}

if (alarme) {
  if(millis() - piscartimer >= 500)
  piscartimer = millis();
  piscarestado = !piscarestado;
  digitalWrite(led4 , piscarestado);

}

if(temp <=80.0 && digitalRead(botao1) == LOW);{
delay(50);
  if (digitalRead(botao1) == LOW) {
    alarme = false;
    digitalWrite(led4, LOW);
    while (digitalRead(botao1) == LOW);

  }
}
  return;
  
  if (digitalRead(botao1) == LOW){
    delay(50);
    if(digitalRead(botao1) == LOW){
      if(!bombaligada && nivel > 15.0){
        bombaligada = true;
      }
     while (digitalRead(botao1) == LOW);
    }
  }
 if (bombaligada &&  nivel< 5.0) {
  bombaligada = false;
 }
 digitalWrite(led1, bombaligada ? HIGH : LOW);
 delay(100);
} 



