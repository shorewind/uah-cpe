% ball toss using vectorization
clear; close all; clc;

g = 9.8;

u_i = 60;

t = 0:0.1:12.3;

y = u_i*t-0.5*g*t.^2;

plot(t, y)
grid on
xlabel('time [sec]')
ylabel('height [m]')
title('Height vs. Time')