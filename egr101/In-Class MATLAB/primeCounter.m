% count how many primes between 0 and N

clc; close

N = input('Enter an integer N: ');

primeCount = 0;
for idx = 2:N
    primeFlag = 1;
    for jdx = 2:idx-1
        if mod(idx, jdx) == 0
            primeFlag = 0;
            break
        end
    end
    primeCount = primeCount + primeFlag;
end

primeCount