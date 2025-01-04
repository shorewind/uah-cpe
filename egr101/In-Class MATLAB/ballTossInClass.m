% ball toss in class

clc; clear; close all;
% initial 
v = 20;
theta = 40;
g = 9.8;

t_hit = 2*v*sind(theta)/g;
t = 0:(t_hit/1000):t_hit;
h = v*t*sind(theta) - (g*t.^2)/2;
v = sqrt(v^2 - 2*v*g*t*sind(theta)+(g^2)*(t.^2));

plot(t,h)
hold on
grid on
plot(t,v)

