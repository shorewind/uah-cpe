% esther shore
% egr-101
% homework 8, question 2

clc; clear; close all;

oddsVector = 0:0.05:1; % zero A loses, one A wins
probability = zeros(1,length(oddsVector)); % vector of probabilities
N_trials = 1000000; % number of trials

for m = 1:length(oddsVector) % outloop odds
    nWinsA = 0; % initialize number of wins for Player A
    for n = 1:N_trials % runs trials
        nWinsA = nWinsA + gamblersRuin(oddsVector(m));
    end
    probability(m) = nWinsA/N_trials; % calculate probabilities
end

% display results
plot(oddsVector, 1 - probability, '--')
grid on
hold on
plot(oddsVector, probability)
title('Gamblers Ruin Problem')
xlabel('Player A P_{win}')
ylabel('Probability')
legend('A Bankrupt','A Not Bankrupt')
savefig('hmwk8Q2.fig')