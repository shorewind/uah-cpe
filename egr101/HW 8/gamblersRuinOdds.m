function [playerAWin] = gamblersRuin(odds)
% a single trial of two gamblers playing
% odds = 0, gambler A always loses odds = 1, gambler wins

playerAMoney = 2;
playerBMoney = 1;

while playerAMoney > 0 && playerBMoney > 0
    play = rand();
    if play < odds % playerA won
        playerAMoney = playerAMoney + 1;
        playerBMoney = playerBMoney - 1;
    else
        playerAMoney = playerAMoney - 1;
        playerBMoney = playerBMoney + 1;
    end
if playerAMoney > 0
    playerAWin = 1;
else
    playerAWin = 0;
end
end