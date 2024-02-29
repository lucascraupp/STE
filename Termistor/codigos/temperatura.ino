float R0 = 9.87e3;
float V = 5.;

void setup(){Serial.begin(9600);}

// Calcula a tensão, com base no valor lido do sensor
float calculaTensao(float d){
  // 5 ---- 1023
  // V ---- d
  return V * d/1023.;
}

// Com base na tensão, obtém o valor da resistência
float calculaRt(float V0){
  float numerador = 0.;

  numerador = R0 * (V - V0);

  return numerador/V0;
}

float calculaTemperatura(float Rt){
  const float A = 1.7426e-04;
  const float B = 3.7782e-04;
  const float C = -4.0342e-07;

  // Minha média = 19.738000
  // Média modelo = 19.023000
  // Erro sitemático = -0.715000

  const float erroSist = -0.715000;
  
  return (1./(A + B * log(Rt) + C * pow(log(Rt), 3))) + erroSist;
}

void loop() {
  int leitura = analogRead(A0); // sample ADC output
  float tensao = calculaTensao(leitura);
  float Rt = calculaRt(tensao);
  
  Serial.print("Resistência de Rt: "); // send value to host
  Serial.print(Rt/1.e3);
  Serial.println(" Kohms");

  Serial.print("Temperatura: ");
  Serial.print(calculaTemperatura(Rt) - 273);
  Serial.println(" °C");
  delay(1000); // wait 1s
}
