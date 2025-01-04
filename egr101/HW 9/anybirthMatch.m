function [y] = anybirthMatch(N)
birthdays = randi([1,365],1,N); % random vector of N birthdays
% if there are fewer unique birthdays than birthdays
% then there is at least one match
if length(birthdays) > length(unique(birthdays)) % ~= also works
    y = 1; % output logical 1 (true)
else
    y = 0; % output logical 0 (false)
end