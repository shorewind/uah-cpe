% esther shore
% egr-101
% homework 7, question 2

clear; clc; close all;

% given sensor sizes in mm
H_FX = 36;
H_DX = 24;

f = 14:800; % vector of focal lengths from 14 to 800 mm

% angle of view functions with vectorization
theta_FX = 2.*atand(H_FX./(2.*f));
theta_DX = 2.*atand(H_DX./(2.*f));

plot(f,theta_FX)
grid on
hold on
plot(f,theta_DX)
xlabel('focal length [mm]')
ylabel('angle of view [deg]')
title('Angle of View for Lens vs. Focal Length')
legend('FX-sensor','DX-sensor')

savefig('hmwk7Q2a.fig')

% plot with x limit
figure
plot(f,theta_FX)
grid on
hold on
plot(f,theta_DX)
xlim([200,800])
xlabel('focal length [mm]')
ylabel('angle of view [deg]')
title('Angle of View for Lens vs. Focal Length - Expanded')
legend('FX-sensor','DX-sensor')

savefig('hmwk7Q2b.fig')

% given distance in ft
R = 300;

% height functions with vectorization
height_FX = R.*deg2rad(theta_FX);
height_DX = R.*deg2rad(theta_DX);

figure
plot(f,height_FX)
grid on
hold on
plot(f,height_DX)
xlim([450,800])
ylim([0,15])
xlabel('focal length [mm]')
ylabel('height [ft]')
title('Height vs. Focal Length')
legend('FX-sensor','DX-sensor','Location','southeast')

savefig('hmwk7Q2c.fig')