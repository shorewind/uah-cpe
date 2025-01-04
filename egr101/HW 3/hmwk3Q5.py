# esther shore
# egr-101
# homework 3, question 5

import math as m

def display_prompt():
    print('This program accepts an acceptable error from the user between the gamma functions.')

# function to approximate value of gamma to N terms

def myGamma(z, N):
    
    myProd = 1
    
    for n in range(1, N+1):
        myProd *= (1+(1/n))**z * (1+(z/n))**(-1)
    Gamma = myProd/z
    return Gamma

def main():
    display_prompt()
    z = eval(input('Enter a value for z: '))  # query the user
    error = eval(input('Enter an acceptable error: '))
    
    N = 1  # initialize number of terms variable
    # while the calculated error is greater than desired, add to number of terms

    while abs(myGamma(z, N) - m.gamma(z)) > error:
        N += 1

    # print result
    
    print(str(N) + ' terms are required to get error within ' + str(error))

    # when z = 5, 233 terms are required to get error within 1

# run main function

if __name__ == '__main__':
    main()
