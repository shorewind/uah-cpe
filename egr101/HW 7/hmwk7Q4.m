% esther shore
% egr-101
% homework 7, question 4

clc; close all; clear;

% range to target vs. time

t = 0:0.01:20; % vector of times 0 to 20 sec, intervals of 0.01 sec

x = -3000 + 300*t; % x equation of motion
y = [15,150,1500]; % y values

% range to the target equations
r1 = sqrt(x.^2+(y(1)-1.5).^2);
r2 = sqrt(x.^2+(y(2)-1.5).^2);
r3 = sqrt(x.^2+(y(3)-1.5).^2);

% graph plots of range to target vs. time
plot(t,r1)
hold on
plot(t,r2)
plot(t,r3)
grid on
xlabel('time [s]')
ylabel('range [m]')
title('Range to Target vs. Time')
legend('h = 15 m','h = 150 m','h = 1500 m')

savefig('hmwk7Q4a.fig')

% elevation angle equations
theta1 = acosd(abs(x./r1));
theta2 = acosd(abs(x./r2));
theta3 = acosd(abs(x./r3));

% graph plots of elevation angle to target vs. time
figure
plot(t,theta1)
hold on
plot(t,theta2)
plot(t,theta3)
grid on
xlabel('time [s]')
ylabel('elevation angle [deg]')
title('Elevation Angle to Target vs. Time')
legend('h = 15 m','h = 150 m','h = 1500 m')

savefig('hmwk7Q4b.fig')
