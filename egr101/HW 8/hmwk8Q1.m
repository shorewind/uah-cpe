% esther shore
% egr-101
% homework 8, question 1

clear; close all; clc;

N = 1000000; % number of trials
count = 0; % initialize counter for number of deaths

% for every trial, run randomDuel() and add to count for every death
for n = 1:N
    count = count + randomDuel();
end

% display results
disp('Number of Deaths:')
disp(count)
disp('Probability of Death:')
prop = count/N; % proportion of trials with death
disp(prop) % probability of death is approximately 0.16