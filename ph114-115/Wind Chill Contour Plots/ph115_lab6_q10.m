% ph115 lab 6 question 10
clc; clear; close all;
T = 30:5:70;
u = 1:5:41;
[T, u] = meshgrid(T, u);
w = 35.74 + 0.6215*T - 35.75*u.^(0.16) + 0.4275*T.*u.^(0.16);

figure
contourf(T, u, w)
colorbar
c = colorbar;
c.Label.String = 'Wind Chill (\circF)';
title('Wind Chill vs. Temperature and Wind Speed')
xlabel('Temperature (\circF)')
ylabel('Wind Speed (mph)')

figure
surfc(T, u, w)
title('Wind Chill vs. Temperature and Wind Speed')
xlabel('Temperature (\circF)')
ylabel('Wind Speed (mph)')
zlabel('Wind Chill (\circF)')
