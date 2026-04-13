#define LED1 7
#define LED2 8
#define LED3 9
#define LED4 10

long int valorAnalogico = 0;  
long int valorPorcentagem = 0; 

void setup() {
 
  pinMode(LED1,OUTPUT);
  pinMode(LED2,OUTPUT);
  pinMode(LED3,OUTPUT);
  pinMode(LED4,OUTPUT);

  Serial.begin(9600);
}

void loop() {
  
  valorAnalogico = analogRead(A0);
  
  valorPorcentagem = (valorAnalogico*100)/1023;  
  Serial.print("Valor Analogico: ");
  Serial.println(valorAnalogico);
  Serial.print("Valor Porcentagem: ");
  Serial.println(valorPorcentagem);
 
  if (valorPorcentagem<=25){  
    digitalWrite(LED1,LOW);
    digitalWrite(LED2,LOW);
    digitalWrite(LED3,LOW);
    digitalWrite(LED4,LOW);
  }
  else if ((valorPorcentagem>=25) && (valorPorcentagem<=50)){  
    digitalWrite(LED1,HIGH);
    digitalWrite(LED2,LOW);
    digitalWrite(LED3,LOW);
    digitalWrite(LED4,LOW);   
  }
  else if ((valorPorcentagem>=50) && (valorPorcentagem<=75)){ 
    digitalWrite(LED1,HIGH);
    digitalWrite(LED2,HIGH);
    digitalWrite(LED3,LOW);
    digitalWrite(LED4,LOW);   
  }
  else if ((valorPorcentagem>=75) && (valorPorcentagem<=90)){
    digitalWrite(LED1,HIGH);
    digitalWrite(LED2,HIGH);
    digitalWrite(LED3,HIGH);
    digitalWrite(LED4,LOW);   
  }
  else{ 
    digitalWrite(LED1,HIGH);
    digitalWrite(LED2,HIGH);
    digitalWrite(LED3,HIGH);
    digitalWrite(LED4,HIGH);    
  }

}
