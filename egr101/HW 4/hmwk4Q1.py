# esther shore
# egr-101
# homework 4, question 1

# define function to determine if a given integer is an Armstrong number
def isArmstrong(N):
    
    num = str(N)  # convert integer to string
    digits = []  # create list for individual digits of number

    # for each index of the string, append the element to the list
    for i in range(len(num)):
        digits.append(num[i])

    # initialize sum variable and calculate the sum of each digit raised to the number of digits
    mySum = 0
    for digit in digits:
        mySum += int(digit)**len(num)

    # if the sum found equals the initial number, then the integer is an Armstrong number
    if mySum == N:
        return True
    else:
        return False


# establish main function to count number of Armstrong numbers in range
def main():
    
    print('This program accepts an integer M and determines how many Armstrong numbers there are between 1 and M.')

    # query the user
    M = int(input('Enter an integer: '))
    
    # initialize counter
    count = 0

    # iterate through numbers in range and add to count if it is an Armstrong number
    for N in range(1, M + 1):
        if isArmstrong(N):
            count += 1

    # print results
    print('There are ' + str(count) + ' Armstrong numbers between 1 and ' + str(M))


# run main function
if __name__ == '__main__':
    main()
