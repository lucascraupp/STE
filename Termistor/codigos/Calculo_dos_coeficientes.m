close all; clear all; clc;

R = [9.8e3 14.33e3 2.93e3];     % Valor dos resistores

T = [27+273 ; 18+273 ; 62+273]; % Temperatura associada a cada resistor

R_log = log(R);
R_3_log = R_log.^3;

m = [1 1 1 ; R_log; R_3_log];

m = transpose(m);

coeficientes = m \ (1./T);

A = coeficientes(1)
B = coeficientes(2)
C = coeficientes(3)
