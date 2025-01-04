% esther shore
% egr-101
% homework 9, question 1

clc; clear; close all;

% birthMatch function
% function [y] = birthMatch(N)
% myBirthday = 150; % establish my birthday as day out of 365
% birthdays = randi([1,365],1,N); % random vector of N birthdays
% if sum(birthdays == myBirthday) > 0 % if there is at least 1 match
%     y = 1; % output logical 1 (true)
% else
%     y = 0; % output logical 0 (false)
% end
% end

nTrials1 = 1000;
nTrials2 = 10000;
nPeople = 1:400;

prob1 = zeros(1,length(nPeople)); % initialize probability vectors
prob2 = zeros(1,length(nPeople));

for N = nPeople % for 1-400 people
    count1 = 0;
    for n = 1:nTrials1 % for 1000 trials
        count1 = count1 + birthMatch(N);
    end
    prob1(N) = count1/nTrials1;
    
    count2 = 0;
    for n = 1:nTrials2 % for 10000 trials
        count2 = count2 + birthMatch(N);
    end
    prob2(N) = count2/nTrials2;
end

% plot results
plot(nPeople, prob1)
hold on
grid on
plot(nPeople, prob2)
title('My Birthday Match Probability')
xlabel('Number of People')
ylabel('Percentage')
legend('1000 trials', '10000 trials')

savefig('hmwk9Q1.fig')