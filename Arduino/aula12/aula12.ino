const int pin_botao_start = 2;
const int pin_botao_stop = 3;
int estado = 0;
int caixaAlta = 0;
int caixaBaixa = 0;
unsigned long tempo_ant = 0, tempo_atual = 0;
const int sensor_caixa_alta = 4;
const int sensor_caixa_baixa = 5;
const int sensor_baixa = 6;
const int sensor_alta = 7;
#define motorAH 8
#define motorH 9


void setup() {
  pinMode(pin_botao_start, INPUT_PULLUP);
  pinMode(pin_botao_stop, INPUT_PULLUP);
  pinMode(sensor_caixa_alta, INPUT);
  pinMode(sensor_caixa_baixa, INPUT);
  pinMode(sensor_alta, INPUT);
  pinMode(sensor_baixa, INPUT);
  pinMode(motorAH, OUTPUT);
  pinMode(motorH, OUTPUT);
}

void loop() {
  bool stop = digitalRead(pin_botao_stop);
  if(stop == 0){
    estado = 0;
  }

  switch(estado){
    case 0:
      bool start = digitalRead(pin_botao_start);
      if(start == 0){
        estado = 1;
        tempo_ant = millis();
      }
      break;
    case 1:
      tempo_atual = millis();
      if(tempo_atual - tempo_ant > 2000){
        estado = 2;
      } 
      break;
    case 2:
      bool sensor3 = digitalRead(sensor_baixa);
      bool sensor4 = digitalRead(sensor_alta);
      if(sensor3 == 1 && sensor4 == 1){
        estado = 3;
      }
      if(sensor3 == 1 && sensor4 == 0){
        estado = 4;
      }
      break;
    case 3:
      bool sensor1 = digitalRead(sensor_caixa_alta);
      digitalWrite(motorAH, HIGH);
      digitalWrite(motorH, LOW);
      if(sensor1 = 1){
        estado = 5;
      }
      break;
    case 4:
      bool sensor2 = digitalRead(sensor_caixa_baixa);
      digitalWrite(motorH, HIGH);
      digitalWrite(motorAH, LOW);
      if(sensor2 = 1){
        estado = 6;
      }
      break;
    case 5:
      digitalWrite(motorAH, LOW);
      digitalWrite(motorH, LOW);
      caixaAlta++;
      estado = 1;
      break;
    case 6:
      digitalWrite(motorAH, LOW);
      digitalWrite(motorH, LOW);
      caixaBaixa++;
      estado = 1;
      break;

    default: 
    estado = 0;
    digitalWrite(motorAH, LOW);
    digitalWrite(motorH, LOW);
  }
}
