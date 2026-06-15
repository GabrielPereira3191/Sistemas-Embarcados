

const int PIN_L = 2;  
const int PIN_D = 3;  

const int PIN_SENSOR_A = 4; 
const int PIN_SENSOR_B = 5;
const int PIN_SENSOR_C = 6; 

const int PIN_SEL_P = 7; 
const int PIN_SEL_M = 8; 
const int PIN_SEL_G = 9; 

const int PIN_MOTOR_E = 10; 
const int PIN_ALARME  = 11; 

enum Tamanho { NENHUM, PEQUENA, MEDIA, GRANDE };

bool sistemaLigado = false;
bool aAnt = false; 

void setup() {
  pinMode(PIN_L, INPUT_PULLUP);
  pinMode(PIN_D, INPUT_PULLUP);
  pinMode(PIN_SENSOR_A, INPUT_PULLUP);
  pinMode(PIN_SENSOR_B, INPUT_PULLUP);
  pinMode(PIN_SENSOR_C, INPUT_PULLUP);
  pinMode(PIN_SEL_P, INPUT_PULLUP);
  pinMode(PIN_SEL_M, INPUT_PULLUP);
  pinMode(PIN_SEL_G, INPUT_PULLUP);

  pinMode(PIN_MOTOR_E, OUTPUT);
  pinMode(PIN_ALARME, OUTPUT);
  digitalWrite(PIN_MOTOR_E, LOW);
  digitalWrite(PIN_ALARME, LOW);
}

void loop() {
  bool liga    = (digitalRead(PIN_L) == LOW);
  bool desliga = (digitalRead(PIN_D) == LOW);

  bool a = (digitalRead(PIN_SENSOR_A) == LOW);
  bool b = (digitalRead(PIN_SENSOR_B) == LOW);
  bool c = (digitalRead(PIN_SENSOR_C) == LOW);

  bool selP = (digitalRead(PIN_SEL_P) == LOW);
  bool selM = (digitalRead(PIN_SEL_M) == LOW);
  bool selG = (digitalRead(PIN_SEL_G) == LOW);

  Tamanho selecionado = NENHUM;
  if (selP) selecionado = PEQUENA;
  else if (selM) selecionado = MEDIA;
  else if (selG) selecionado = GRANDE;

  if (desliga) {
    sistemaLigado = false;
  }
  if (liga) {
    sistemaLigado = true;
    digitalWrite(PIN_ALARME, LOW); 
  }

  if (!sistemaLigado) {
    digitalWrite(PIN_MOTOR_E, LOW);
    aAnt = a;
    return;
  }

  
  if (digitalRead(PIN_ALARME) == HIGH) {
    digitalWrite(PIN_MOTOR_E, LOW);
    aAnt = a;
    return;
  }

  digitalWrite(PIN_MOTOR_E, HIGH);

  
  if (aAnt && !a) {
    Tamanho detectado;
    if (c)      detectado = GRANDE;
    else if (b) detectado = MEDIA;
    else        detectado = PEQUENA;

    if (detectado != selecionado) {
      digitalWrite(PIN_ALARME, HIGH);
      digitalWrite(PIN_MOTOR_E, LOW);
    }
  }

  aAnt = a;
}
