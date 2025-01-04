function [myFact] = myFactorial(N)
    myFact = 1; % initialized to unity
    for n = 1:N
        myFact = myFact*n;
    end
end