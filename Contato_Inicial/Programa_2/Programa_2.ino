// Valor mínimo e máximo do potenciômetro
#define minPot 0.0  
#define maxPot 1023.0

// Valor mínimo e máximo o LED
#define minLed 0.0
#define maxLed 255.0

#define R 10.0e3  // Resistência do potenciômetro
#define Vcc 5.0   // Tensão do Arduino.

void setup(void) {
  Serial.begin(9600);
  pinMode(3, OUTPUT);
}

void loop(void) {
  float valorPot = analogRead(A0);  // Obtém o valor analógico do potenciômetro

  float Vout = valorPot/maxPot * Vcc;
  Serial.println(Vout);
  
  float valorLed = (valorPot - minPot) * (maxLed - minLed)/(maxPot - minPot) + minLed;  // Função map(), porém retornando valores decimais
  
  analogWrite(3, valorLed); // Envia o valor da luminosidade, para o LED
  delay(1000);
  
}
