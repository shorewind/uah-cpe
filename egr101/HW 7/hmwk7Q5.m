% esther shore
% egr-101
% homework 7, question 5

clc; clear; close all;

load('hmwk7StockData.mat') % load the data

% plot the data
plot(Date,fconx)
hold on
grid on
plot(Date,fsggx)
plot(Date,fskax)

% label the figure
xlabel('Date')
ylabel('Closing $')
title('Mutual Fund Prices vs. Time')
legend('FCONX','FSGGX','FSKAX')

savefig('hmwk7Q5.fig')

% get max/min value and index from fconx and retrieve date at index
[max_fconx,idx] = max(fconx);
disp('FCONX Max:')
disp(max_fconx)
disp(Date(idx))
[min_fconx,idx] = min(fconx);
disp('FCONX Min:')
disp(min_fconx)
disp(Date(idx))

% get max/min value and index from fsggx and retrieve date at index
[max_fsggx,idx] = max(fsggx);
disp('FSGXX Max:')
disp(max_fsggx)
disp(Date(idx))
[min_fsggx,idx] = min(fsggx);
disp('FSGGX Min:')
disp(min_fsggx)
disp(Date(idx))

% get max/min value and index from fskax and retrieve date at index
[max_fskax,idx] = max(fskax);
disp('FSKAX Max:')
disp(max_fskax)
disp(Date(idx))
[min_fskax,idx] = min(fskax);
disp('FSKAX Min:')
disp(min_fskax)
disp(Date(idx))