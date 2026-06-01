const int potenciometro = A0;
const int exaustor = 9;
const int ledmax = 10;

void setup (){
  pinMode(exaustor, OUTPUT);
  pinMode(ledmax, OUTPUT);
  Serial.begin(9600);
}
void loop(){ 
  int leitura = analogRead(potenciometro);
  float temperatura = map(leitura,0,1023,0,100);
  
  int potencia = 0;

  if (temperatura < 30.0) {
    potencia = 51;
    digitalWrite(ledmax, LOW);

  } else if (temperatura <= 60.0){
    potencia = map(temperatura,30,60,51,255);
    digitalWrite(ledmax, LOW);

  } else {
    potencia = 255;
    digitalWrite(ledmax, HIGH);
  }
  analogWrite(exaustor, potencia);

  Serial.print("temp:");
  Serial.print(temperatura);
  Serial.print ("c | potencia:");
  Serial.print((potencia / 255.0) * 100.0); 
  Serial.println("%");

  delay(200);
}