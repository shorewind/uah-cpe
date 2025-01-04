% leibnitz.pi

N = input('Enter the Number of Terms in Leibnitz: ');

myPiBy4 = 0;

for n = 0:N
    
    myPiBy4 = myPiBy4 + ((-1)^n) / (2*n+1);
    
end

display(4*myPiBy4)