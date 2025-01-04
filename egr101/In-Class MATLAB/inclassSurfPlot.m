% class saddle point and more
clc; close all; clear

[x,y] = meshgrid(-1:0.1:1); % table cloth

z = x.^2 - y.^2;
surf(x,y,z)
xlabel('x')
ylabel('y')
zlabel('z')
title('Saddle Point Plot')
colorbar
figure
contour(x,y,z)
title('Contour Plot')
figure
z = x.^3 - 3*x.*y.^2;
surf(x,y,z)
title('Monkey Saddle Plot')