% esther shore
% egr-101
% homework 8, question 5

clear; clc; close all;

N = 1000000; % number of trials
x = 1:12; % number of sixes
probability = zeros(1,length(x)); % initialize probability vector

for n = x % for each number of sixes
    count = 0; % initialize counter
    for nTrial = 1:N % for each trial
        diceRolls = randi(6,1,n*6); % n*6 represents number of dice rolls
        % if number of sixes found in diceRolls is greater than or equal to
        % threshold number of sixes n, add to count
        if sum(diceRolls == 6) >= n
            count = count + 1;
        end
    end
    probability(n) = count/N; % add probabilities to probability vector
end

% display results
stem(x,probability)
grid on
title('Multiple Dice Experiment')
xlabel('Number of Sixes')
ylabel('Probability')
savefig('hmwk8Q5b.fig')