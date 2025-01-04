function [y] = birthMatch(N)
myBirthday = 150; % establish my birthday as day out of 365
birthdays = randi([1,365],1,N); % random vector of N birthdays
if sum(birthdays == myBirthday) > 0 % if there is at least 1 match
    y = 1; % output logical 1 (true)
else
    y = 0; % output logical 0 (false)
end
end