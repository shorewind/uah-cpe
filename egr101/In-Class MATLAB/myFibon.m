function [output] = myFibon(N)
% RECURSIVE METHOD fibonacci series
    if N == 1
        output = 1;
    elseif N == 2
        output = 1;
    else
        output = myFibon(N-1) + myFibon(N-2);
    end
end