#define botaoPulso 5
#define saidaLed   9

const long int intervalo = 200;
int tempoAtual = 0, tempoAnterior = 0;
int controleLed = 0;
long int saidaAnalogica = 0;
int tempoFiltroBotao = 0;
bool auxPulso = 0;

void setup() {
  
  pinMode(botaoPulso, INPUT_PULLUP);
  pinMode(saidaLed, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  
 tempoAtual = millis(); 

  if (tempoAtual - tempoAnterior >= intervalo) {
    tempoAnterior = tempoAtual; 
    tempoFiltroBotao = 1;       
  }

  if ((!digitalRead(botaoPulso)) && (!auxPulso) && (tempoFiltroBotao)){ 
    controleLed = controleLed+25;     
    if (controleLed>100){
      controleLed = 0;
    }                     
    auxPulso = 1; 
  }
  else if (digitalRead(botaoPulso)){ 
    auxPulso = 0;
    tempoFiltroBotao = 0;
  }

  saidaAnalogica = (controleLed*255)/100;
  analogWrite(saidaLed, saidaAnalogica);

 
