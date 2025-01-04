% esther shore
% egr-101
% homework 9, question 2

clc; clear; close all;

% anybirthMatch function
% function [y] = anybirthMatch(N)
% birthdays = randi([1,365],1,N); % random vector of N birthdays
% % if there are fewer unique birthdays than birthdays
% % then there is at least one match
% if length(birthdays) > length(unique(birthdays)) % ~= also works
%     y = 1; % output logical 1 (true)
% else
%     y = 0; % output logical 0 (false)
% end

nTrials1 = 1000;
nTrials2 = 10000;
nPeople = 1:400;

prob1 = zeros(1,length(nPeople)); % initialize probability vectors
prob2 = zeros(1,length(nPeople));

for N = nPeople % for 1-400 people
    count1 = 0;
    for n = 1:nTrials1 % for 1000 trials
        count1 = count1 + anybirthMatch(N);
    end
    prob1(N) = count1/nTrials1;
    
    count2 = 0;
    for n = 1:nTrials2 % for 10000 trials
        count2 = count2 + anybirthMatch(N);
    end
    prob2(N) = count2/nTrials2;
end

% plot results
plot(nPeople, prob1)
hold on
grid on
plot(nPeople, prob2)
title('Any Birthday Match Probability')
xlabel('Number of People')
ylabel('Percentage')
legend('1000 trials', '10000 trials')

savefig('hmwk9Q2.fig')