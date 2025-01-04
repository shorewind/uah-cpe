function [death] = randomDuel()
time1 = randi([0,3600]); % establish time of arrival for each
time2 = randi([0,3600]); % simplified to a second within an hour

% if the difference between them is less than 5 min, a death occurs
    if abs(time1 - time2) <= 300
        death = 1;
    else
        death = 0;
    end
end