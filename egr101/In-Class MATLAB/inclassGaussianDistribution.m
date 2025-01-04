clc; close all; clear
[x,y] = meshgrid(-5:0.25:5);

sx = 1; % covariance parameter
sy = 2;

z = exp(-(x.^2/sx^2 + y.^2/sy^2));
surf(x,y,z)
xlabel('x')
ylabel('y')
zlabel('z')
title('Gaussian Plot')
colorbar