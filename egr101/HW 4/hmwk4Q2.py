# esther shore
# egr-101
# homework 4, question 2

# function to approximate pi using abraham series
def abr_pi(N):

    myPi = 0  # initialize sum
    
    # iterate through range and add each term to sum
    for n in range(0,N+1):
        myPi += (2*(-1)**n * 3**(1/2 - n))/(2*n + 1)
        
    return myPi

# main function to accept an integer for the number of terms and return the approximation of pi
def main():

    print('This program estimated pi computing the Abraham Series using N terms.')

    N = int(input('Enter an integer: '))  # query the user
    
    print('The approximation of pi is: ' + str(abr_pi(N)))  # print result

if __name__ == '__main__':
    main()
