close; clear; clc;

x = 0:0.01:5;

subplot(2,1,1)
plot(x, sin(2*pi*x))
hold on
subplot(2,1,2)
plot(x, cos(2*pi*x))
