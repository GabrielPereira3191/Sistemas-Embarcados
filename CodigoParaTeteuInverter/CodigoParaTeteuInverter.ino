unsigned long tempo = 0;
unsigned long auxiliar = 0;

const int sensor1 = 4;  // Sensor 1
const int sensor2 = 2;  // Sensor 2
const int sensor3 = 7;  // Sensor 3
const int sensor4 = 8;  // Sensor 4
const int sensor5 = 12;  // Sensor 5

// Definição de pinos para controle do motor
int veloE = 11;
int veloD = 3;
int frenteE = 9;
int trasE = 10;
int frenteD = 6;
int trasD = 5;

void setup() {
  // Inicializar sensores como entrada
  pinMode(sensor1, INPUT);
  pinMode(sensor2, INPUT);
  pinMode(sensor3, INPUT);
  pinMode(sensor4, INPUT);
  pinMode(sensor5, INPUT);

  // Inicializar motores como saída
  pinMode(frenteE, OUTPUT);
  pinMode(trasE, OUTPUT);
  pinMode(frenteD, OUTPUT);
  pinMode(trasD, OUTPUT);
}

void loop() {
  tempo = millis();
  // Leitura dos sensores de linha
  int sensorL1 = digitalRead(sensor1);
  int sensorL2 = digitalRead(sensor2);
  int sensorL3 = digitalRead(sensor3);
  int sensorL4 = digitalRead(sensor4);
  int sensorL5 = digitalRead(sensor5);

  // Se o centro está na linha, o robô anda reto
  if (sensorL3 == LOW && sensorL1 == HIGH && sensorL2 == HIGH && sensorL4 == HIGH && sensorL5 == HIGH) {
    andarReto();
  }
  // Se o sensor da esquerda está na linha, o robô vira para a direita
  else if (sensorL1 == HIGH && sensorL2 == LOW && sensorL3 == LOW && sensorL4 == LOW && sensorL5 == LOW) {
    virarEsquerdaCurva();
  }
  // Se o sensor da direita está na linha, o robô vira para a esquerda
  else if (sensorL1 == HIGH && sensorL2 == HIGH && sensorL3 == LOW && sensorL4 == LOW && sensorL5 == LOW) {
    virarEsquerdaCurva();
  }
  // Caso o sensor da direita mais a frente esteja na linha, vira para a esquerda
  else if (sensorL1 == HIGH && sensorL2 == HIGH && sensorL3 == HIGH && sensorL4 == LOW && sensorL5 == LOW) {
    virarEsquerdaCurva();
  }
  // Caso o sensor da esquerda mais a frente esteja na linha, vira para a direita
  else if (sensorL1 == LOW && sensorL2 == HIGH && sensorL3 == LOW && sensorL4 == LOW && sensorL5 == LOW) {
    virarEsquerda();
  } else if (sensorL1 == LOW && sensorL2 == HIGH && sensorL3 == HIGH && sensorL4 == LOW && sensorL5 == LOW) {
    virarEsquerdaCurva();
  } else if (sensorL1 == LOW && sensorL2 == LOW && sensorL3 == LOW && sensorL4 == LOW && sensorL5 == HIGH) {
    virarDireitaCurva();
  } else if (sensorL1 == LOW && sensorL2 == LOW && sensorL3 == LOW && sensorL4 == HIGH && sensorL5 == HIGH) {
    virarDireitaCurva();
  } else if (sensorL1 == LOW && sensorL2 == LOW && sensorL3 == HIGH && sensorL4 == HIGH && sensorL5 == HIGH) {
    virarDireitaCurva();
  } else if (sensorL1 == LOW && sensorL2 == LOW && sensorL3 == HIGH && sensorL4 == HIGH && sensorL5 == LOW) {
    virarDireitaCurva();
  } else if (sensorL1 == LOW && sensorL2 == LOW && sensorL3 == LOW && sensorL4 == HIGH && sensorL5 == LOW) {
    virarDireita();
  } else if (sensorL1 == LOW && sensorL2 == LOW && sensorL3 == LOW && sensorL4 == LOW && sensorL5 == LOW) {
    mantervelo();
  } else if (sensorL1 == HIGH && sensorL2 == HIGH && sensorL3 == HIGH && sensorL4 == HIGH && sensorL5 == HIGH) {
    andarReto();
  }
}


void andarReto() {
  digitalWrite(frenteE, HIGH);
  digitalWrite(trasE, LOW);
  digitalWrite(frenteD, HIGH);
  digitalWrite(trasD, LOW);
  analogWrite(veloE, 210);
  analogWrite(veloD, 210);
}
void mantervelo() {
  digitalWrite(frenteE, HIGH);
  digitalWrite(trasE, LOW);
  digitalWrite(frenteD, HIGH);
  digitalWrite(trasD, LOW);
  analogWrite(veloE, 120);
  analogWrite(veloD, 120);
}

void virarDireitaCurva() {
  digitalWrite(frenteE, HIGH);
  digitalWrite(trasE, LOW);
  digitalWrite(frenteD, LOW);
  digitalWrite(trasD, HIGH);
  analogWrite(veloE, 220);
  analogWrite(veloD, 170);
}

void virarEsquerdaCurva() {
  digitalWrite(frenteE, LOW);
  digitalWrite(trasE, HIGH);
  digitalWrite(frenteD, HIGH);
  digitalWrite(trasD, LOW);
  analogWrite(veloE, 170);
  analogWrite(veloD, 220);
}

void parar() {
  digitalWrite(frenteE, LOW);
  digitalWrite(trasE, LOW);
  digitalWrite(frenteD, LOW);
  digitalWrite(trasD, LOW);
  analogWrite(veloE, 0);
  analogWrite(veloD, 0);
}
void virarEsquerda() {
  digitalWrite(frenteE, HIGH);
  digitalWrite(trasE, LOW);
  digitalWrite(frenteD, HIGH);
  digitalWrite(trasD, LOW);
  analogWrite(veloE, 120);
  analogWrite(veloD, 200);
}
void virarDireita() {
  digitalWrite(frenteE, HIGH);
  digitalWrite(trasE, LOW);
  digitalWrite(frenteD, HIGH);
  digitalWrite(trasD, LOW);
  analogWrite(veloE, 200);
  analogWrite(veloD, 120);
}