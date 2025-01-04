# esther shore
# egr-101
# homework 4, question 3

import math as m

# abraham series to compute pi as in question 2
def abr_pi(N):
    
    myPi = 0
    
    for n in range(0,N+1):
        myPi += (2*(-1)**n * 3**(1/2 - n))/(2*n + 1)
        
    return myPi

# main function to accept an integer and determine the number of terms required for a given error
def main():

    print('This program determines the number of terms N to achieve an estimate of pi within 10^(-M)')

    M = int(input('Enter an integer: '))  # query the user

    N = 1  # initialize number of terms counter

    # while the calculated error is greater than desired, increase the number of terms by 1
    while abs(abr_pi(N) - m.pi) > 10**(-M):
        N += 1

    # print result
    print(str(N) + ' terms are required to get error within ' + str(10**(-M)))

    # when M = 9, N = 16 

if __name__ == '__main__':
    main()
