# esther shore
# egr-101
# homework 3, question 3

import math as m

def display_prompt():
    print('This program accepts an integer N and determines the number of strong numbers between 2 and N.')

# create function to determine if an integer is a strong number

def is_strong(n):
    
    # turn integer into string, split digits, and add to list
    
    num = str(n)
    myList = []
    for i in range(0, len(num)):
        myList.append(num[i])
        
    # establish sum variable
    # determine if integer equals the sum of the factorials of the digits
    
    mySum = 0
    for number in myList:
        mySum += m.factorial(int(number))
    if mySum == n:
        return True
    else:
        return False

# create main function

def main():
    display_prompt()
    N = int(input('Enter an integer: '))  # query the user
    count = 0  # create count variable

    # add one to count for each number in range that is a strong number

    for num in range(2, N + 1):
        if is_strong(num):
            count += 1

    # print result
    
    print('There are ' + str(count) + ' strong numbers between 2 and ' + str(N))

    # there are 4 strong numbers between 1 and 100451 (1, 2, 145, and 40585)

# run main function

if __name__ == '__main__':
    main()
