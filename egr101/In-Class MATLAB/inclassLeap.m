% leap year

clc; clear;

year = input('Enter a Year: ');

if mod(year, 4) ~= 0
    isPrime = 0;
else
    if mod(year, 100) ~= 0
        isPrime = 1;
    else
        if mod(year, 400) == 0
            isPrime = 1;
        else
            isPrime = 0;
        end
    end
end
disp(isPrime)