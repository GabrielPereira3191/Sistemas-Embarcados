const int botaoA  = 2;  
const int botaoB  = 3;  
const int esteira = 8; 


int contadorLote  = 0;  
int totalCaixas   = 0;  

bool esteiraAtiva     = false;
bool aguardandoReset  = false;
bool pausada          = false;


bool ultimoEstadoB        = HIGH;
unsigned long debounceB   = 0;
const unsigned long DEBOUNCE_MS = 50;


unsigned long tempoPausa  = 0;
const unsigned long PAUSA_MS = 3000; 

void setup() {
  pinMode(botaoA, INPUT_PULLUP);
  pinMode(botaoB, INPUT_PULLUP);
  pinMode(esteira, OUTPUT);
  Serial.begin(9600);
  Serial.println("Sistema aguardando Botão A para iniciar...");
}

void loop() {

  
  if (digitalRead(botaoA) == LOW) {
    delay(50); 
    if (digitalRead(botaoA) == LOW) {

      if (!esteiraAtiva && !aguardandoReset) {
        
        esteiraAtiva    = true;
        contadorLote    = 0;
        totalCaixas     = 0;
        pausada         = false;
        digitalWrite(esteira, HIGH);
        Serial.println(">>> Esteira INICIADA.");

      } else if (aguardandoReset) {
        
        aguardandoReset = false;
        esteiraAtiva    = true;
        contadorLote    = 0;
        totalCaixas     = 0;
        pausada         = false;
        digitalWrite(esteira, HIGH);
        Serial.println(">>> Sistema RESETADO. Esteira INICIADA.");
      }

     
      while (digitalRead(botaoA) == LOW);
    }
  }

  
  if (!esteiraAtiva || aguardandoReset) return;

 
  if (pausada) {
    if (millis() - tempoPausa >= PAUSA_MS) {
      pausada = false;
      digitalWrite(esteira, HIGH);
      Serial.println(">>> Esteira RETOMADA.");
    } else {
      return; 
    }
  }

  
  bool leituraB = digitalRead(botaoB);

  if (leituraB != ultimoEstadoB) {
    debounceB = millis();
  }

  if ((millis() - debounceB) > DEBOUNCE_MS) {
    if (leituraB == LOW && ultimoEstadoB == HIGH) {
     
      contadorLote++;
      totalCaixas++;

      Serial.print("Caixa detectada! Lote: ");
      Serial.print(contadorLote);
      Serial.print("/5  |  Total: ");
      Serial.println(totalCaixas);

      
      if (contadorLote >= 5) {
        contadorLote = 0;
        pausada      = true;
        tempoPausa   = millis();
        digitalWrite(esteira, LOW);
        Serial.println("--- Braço pneumático atuando (3s)...");
      }

    
      if (totalCaixas >= 20) {
        esteiraAtiva    = false;
        aguardandoReset = true;
        pausada         = false;
        digitalWrite(esteira, LOW);
        Serial.println("=== 20 caixas atingidas. Pressione Botão A para RESET. ===");
      }
    }
  }

  ultimoEstadoB = leituraB;
}