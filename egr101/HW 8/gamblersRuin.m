function [playerAWin] = gamblersRuin(odds)
% a single trial of two gamblers playing
% odds = 0, gambler A always loses odds = 1, gambler wins

playerAMoney = 2;
playerBMoney = 1;

while playerAMoney > 0 && playerBMoney > 0  % while both players have money
    play = rand();
    if play < odds % if player A's odds are greater than play
        playerAMoney = playerAMoney + 1; % player A gains
        playerBMoney = playerBMoney - 1; % player B loses
    else
        playerAMoney = playerAMoney - 1; % player A loses
        playerBMoney = playerBMoney + 1; % player B gains
    end
if playerAMoney > 0 % if player A has money and is not bankrupt
    playerAWin = 1; % player A wins
else
    playerAWin = 0; % player A loses and goes bankrupt
end
end