# amicable number program

# displays what program does

print('This program accepts two integers and determines whether they are amicable.')

# user entry for two integers

M = int(input('Enter the first number to test: '))
N = int(input('Enter the second number to test: '))

# form two summations for the respective factors

sumFactorM = 0
sumFactorN = 0

# find the factors of M

for m in range(1,M):
    if M % m == 0:  # factor is found for M
        sumFactorM += m

# find the factors of N

for n in range(1,N):
    if N % n == 0:  # factor is found for N
        sumFactorN += n

if (sumFactorM == N and sumFactorN == M):
    print('amicable')
else:
    print('not amicable')
