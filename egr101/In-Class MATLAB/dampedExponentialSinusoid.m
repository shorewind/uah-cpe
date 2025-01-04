% damped exponential sinusoid
    clc; close all; clear

t = 0:0.01:10;

tone = cos(2*2*pi*t);
decay = exp(-0.5*t);

% subplot(2, 1, 1)
plot(t, decay)
hold on
plot(t, tone, 'k--')
grid
xlabel('t [s]')
ylabel('amplitude of the tone')
title('Damped Exponential Sinusoid')

% subplot(2, 1, 2)
figure % new figure
plot(t, decay.*tone)
