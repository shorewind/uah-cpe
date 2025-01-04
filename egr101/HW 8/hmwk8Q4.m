% esther shore
% egr-101
% homework 8, question 4

clc; clear; close all;

N = 100000; % number of trials
tally = 0; % initialize total number of matches

for n = 1:N % for each trial
    tally = tally + myDeckExperimentTwo();
end

avg_matches = tally/N; % compute average number of matches
disp(avg_matches) % average number of matches is approximately 4