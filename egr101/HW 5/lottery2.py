# esther shore
# egr-101
# homework 5, question 2

import random as r

# function to generate list with 5 random integers representing lottery pick
def lotteryPick(M):

    # if M is less than 5, return empty list
    while M < 5:
        empty_list = []
        return empty_list
    
    # otherwise return list of 5 random integers from 1 to M
    return r.sample(range(1, M + 1), 5)

# main function to determine the counts and probabilities for each number of matches over some number of trials using user input
def lottery2(): 

    # query the user
    M = int(input('Enter M, the lottery range, 1 to M of the drawing: '))

    while M < 5:
        M = int(input('Enter an integer M greater than or equal to 5: ')) 

    N = int(input('Enter an integer N for the number of times you want to play 10^N: '))

    # establish dictionary with the keys being the number of possible matches and the values being the corresponding number of each
    d = {match:0 for match in range(0,6)}  # d = {0: 0, 1: 0, 2: 0, 3: 0, 4: 0, 5: 0}

    # for each trial
    for n in range(10**N):
        
        # lottery picks for user and actual
        actual_drawing = lotteryPick(M)
        Quick_Pick = lotteryPick(M)

        # initialize count for number of matches
        count = 0

        # determine how many matches if any
        for num1 in actual_drawing:
            for num2 in Quick_Pick:
                if num1 == num2:
                    count += 1

        # add to corresponding value to track number of times getting each amount of matches
        for i in range(0,6):
            if count == i:
                d[i] += 1

    # print results           
    print('Counts for each number of matches over 10^N trials:')        
    print(d)

    # for each value, divide by the number of terms to get the proportion of each number of matches
    for i in range(0,6):
        d[i] = d[i] / (10**N)

    # print results
    print('Probabilities for each number of matches:')
    print(d)

# run main function
lottery2()
    
