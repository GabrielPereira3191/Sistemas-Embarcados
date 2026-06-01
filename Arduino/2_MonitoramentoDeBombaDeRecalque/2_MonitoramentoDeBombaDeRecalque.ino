const int ledmotor = 9;
const int ledverificar = 10;
const int botaoinicio = 2;
const int botaocontagem = 3;
 
 int contagem = 0;
 bool motorligado = false;
 bool ultimobotaocontagem = HIGH;
 bool ultimobotaoinicio = HIGH;


 void setup() {
 pinMode(botaoinicio, INPUT_PULLUP);
 pinMode(botaocontagem, INPUT_PULLUP);
 pinMode(ledmotor, OUTPUT);
 pinMode(ledverificar, OUTPUT);
 Serial.begin(9600);
 }

 void loop() {
  bool botaoInicio = digitalRead(botaoinicio);
  bool botaoContagem = digitalRead(botaocontagem);

  if (botaoinicio == LOW && ultimobotaoinicio == HIGH) {
    contagem = 0;
    motorligado = true;
   digitalWrite(ledmotor, HIGH);
    digitalWrite(ledverificar, LOW);
   Serial.println("contagem = 0");
  }
  ultimobotaoinicio = botaoinicio;

  if (botaocontagem == LOW && ultimobotaocontagem == HIGH && motorligado) {
    contagem ++;
    Serial.print("contagem:");
    Serial.print(contagem);

    if (contagem >= 60) {
      motorligado = false;
      digitalWrite(ledmotor, LOW);
        for (int i = 0;i < 10; i++){
          digitalWrite(ledverificar, HIGH);
          delay(300);
          digitalWrite(ledverificar, LOW);
          delay(300);
        }
    }
  }
  ultimobotaocontagem = botaocontagem;
 }


