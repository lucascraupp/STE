enum estados{
  off = 0,
  on = 1,
  w1 = 2,
  w2 = 3,
};

volatile int botao = 0;
estados state = off;

unsigned long tempoRepique = 200; // Tempo necesário para ignorar o repique
unsigned long ultMod = 0;         // Momento que ocorreu a última modificação no estado do led

void setup() {
  pinMode(2, INPUT);
  pinMode(13, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(2), handleButton, RISING);
}

void loop() {
  // Impede a concorrência pelo uso do botão
  noInterrupts();
  int b = botao;
  botao = 0;
  interrupts();
  
  switch(state){
    // Estado onde o led se encontra apagado, até pressionar o botão
    case off:   
      if(b == 1){
        state = w1;
        digitalWrite(13, HIGH);
      }
              
      break;

    // Estado intermediário entre desligado e ligado
    case w1:
      noInterrupts();
      state = on;
      delay(tempoRepique);
      ultMod = millis();
      interrupts();
     
      break;

    // Estado onde o led se encontra aceso, até pressionar o botão
    case on:
      if(b == 1){
        state = w2;
        digitalWrite(13, LOW);
      }

      break;

    // Estado intermediário entre ligado e desligado
    case w2:
      noInterrupts();
      state = off;
      delay(tempoRepique);
      ultMod = millis();
      interrupts();

      break;

    default:
      break;
  }

  delay(1);
}

void handleButton(){
  unsigned long tempo = millis(); // Obtém o tempo (em milissegundos) que se passou, desde que o programa começou a executar

  if(tempo - ultMod >= tempoRepique){
    ultMod = tempo;
    botao = 1;
  }
}
