% esther shore
% egr-101
% homework 7, question 1

clear; clc; close all;

% given sensor sizes in mm
H_FX = 36;
H_DX = 24;

f = 14:800; % vector of focal lengths from 14 to 800 mm

% form angle of view vectors of length f
theta_FX = zeros(1,length(f));
theta_DX = zeros(1,length(f));

for idx = 1:length(f) % index runs the length of f
    theta_FX(idx) = 2*atand(H_FX/(2*f(idx)));
    theta_DX(idx) = 2*atand(H_DX/(2*f(idx)));
end

% graph and label
plot(f,theta_FX)
grid on
hold on
plot(f,theta_DX)
xlabel('focal length [mm]')
ylabel('angle of view [deg]')
title('Angle of View for Lens vs. Focal Length')
legend('FX-sensor','DX-sensor')

savefig('hmwk7Q1a.fig')

% figure with x limit
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

savefig('hmwk7Q1b.fig')

% given distance in ft
R = 300;

% form height vectors of length f
height_FX = zeros(1,length(f));
height_DX = zeros(1,length(f));

for idx = 1:length(f) % index runs the length of f
    height_FX(idx) = R*deg2rad(theta_FX(idx));
    height_DX(idx) = R*deg2rad(theta_DX(idx));
end

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

savefig('hmwk7Q1c.fig')