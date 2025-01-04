function [out] = myRecFactorial(N)
if N == 1
    out = 1;
else
    out = N*myRecFactorial(N-1);
end
end

