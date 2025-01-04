% esther shore
% egr-101
% homework 10, question 1

clc; clear; close all;

D = 1; % length of sides of square
L = 0.5; % length of sticks

power = 1:6;
nSticks = 10.^power;
myPi = zeros(1,length(nSticks)); % initialize vector for estimates of pi

for i = 1:length(nSticks) % index
    C = 0; % initialize number of crossings
    for N = 1:nSticks(i) % trials
        % center point coordinates
        xc = rand; 
        yc = rand;

        theta = rand*360; % scale random number by 360
        
        % coordinates of stick tips
        xt1 = xc + (L/2)*cosd(theta);
        yt1 = yc + (L/2)*sind(theta);
        xt2 = xc -(L/2)*cosd(theta);
        yt2 = yc - (L/2)*sind(theta);

        % determine if the stick crosses out of the square
        didCrossX = (xt1 < 0 || xt1 > D || xt2 < 0 || xt2 > D);
        didCrossY = (yt1 < 0 || yt1 > D || yt2 < 0 || yt2 > D);

        % add to number of crossings
        C = C + didCrossX + didCrossY;
    end
    myPi(i) = (4*L*N)/(D*C); % calculate estimate of pi for each number of sticks
end

% plot results
stem(power, myPi)
grid on
xlabel('Number of Sticks Tossed (10^x)')
ylabel('Estimate of pi')
title("Estimating Pi Using Buffon's Experiment")

savefig('hmwk10Q1.fig')