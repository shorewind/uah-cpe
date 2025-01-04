# esther shore
# egr-101
# homework 3, question 4

import math as m

def display_prompt():
    print('This program estimates the value of Gamma from a finite series to N terms.')

# define function to estimate Gamma

def myGamma(z, N):
    myProd = 1  # initialize product

    # multiply each term together
    for n in range(1, N+1):
        myProd *= (1+(1/n))**z * (1+(z/n))**(-1)
    Gamma = myProd/z
    return Gamma

# establish main function to get inputs from user and print results

def main():
    display_prompt()
    z = eval(input('Enter a real number z: '))  # query the user
    N = int(input('Enter an integer N: '))

    # print result
    
    print('The approximation of Gamma is ' + str(myGamma(z, N)))
    print('The actual value of Gamma is ' + str(m.gamma(z)))

# run main function

if __name__ == '__main__':
    main()
