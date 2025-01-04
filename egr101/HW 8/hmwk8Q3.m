% esther shore
% egr-101
% homework 8, question 3

clc; clear; close all;

N = 100000; % number of trials
count = 0; % initialize total number of matches

for n = 1:N % for each trial
    count = count + myDeckExperiment();
end

avg_matches = count/N; % compute average number of matches
disp(avg_matches) % average number of matches is approximately 1