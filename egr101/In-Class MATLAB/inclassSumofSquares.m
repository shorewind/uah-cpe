% for loop to check the vector summation squared result
clc; % clears the command window
close all; % clears figures
clear; % cleras workspace

tic
N = 1000;
mySumofSquares = 0; % initialized to zero

for n = 1:N
    mySumofSquares = mySumofSquares + (n ^ 2);
end

mySumofSquares
toc

% compare elapsed time to:
tic; myans1 = sum((1:N).^2); toc
tic; myans2 = N*(N+1)*(2*N+1)/6; toc
