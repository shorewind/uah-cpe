% esther shore
% egr-101
% homework 10, question 2

clc; clear; close all;

power = 1:6;
nTrials = 10.^power;
myE = zeros(1,length(nTrials)); % initialize vector for estimates of e

for i = 1:length(nTrials) % index
    D = 0; % initialize number of derangements
    for N = 1:nTrials(i) % trials
        % two shuffled decks
        deck1 = randperm(52);
        deck2 = randperm(52);

        matches = sum(deck1 == deck2); % number of matches between the decks

        if matches == 0 % if there are no matches, it is a derangement
            D = D + 1;
        end
        
        myE(i) = N/D; % calculate estimate of e for each number of trials
    end
end

% plot results
stem(power, myE)
grid on
xlabel('Number of Trials (10^x)')
ylabel('Estimate of e')
title('Estimating e Using Derangements of Shuffled Decks')

savefig('hmwk10Q2.fig')