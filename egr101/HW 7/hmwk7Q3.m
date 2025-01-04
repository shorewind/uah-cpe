% esther shore
% egr-101
% homework 7, question 3

clc; close all; clear;

N = 10;
my_e = 0; % initialize sum
% initialize vector to hold values after each term is added
values = zeros(1,length(N));

for n = 0:N % for each value of n in range 0 to N
    my_e = my_e + 1/factorial(n); % add term to my_e
    values(n+1) = my_e; % add value of my_e to values
end

% create bar graph
bar(values)
grid on
xlabel('Number of Terms')
title('Approximation for E Using Series')

savefig('hmwk7Q3.fig')

my_e;
% MATLAB's value for e = exp(1) = 2.7183...
matlab_e = exp(1);
% my_e is approximately equal to exp(1)

% one-line command using vectorization
sum_e = sum(1./factorial(0:N));
% my_e is approximately equal to sum(1./factorial(0:N)) = 2.7183...