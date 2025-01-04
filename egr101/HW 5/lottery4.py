# esther shore
# egr-101
# homework 5, question 4

import random as r

# function to generate list with 5 random integers representing lottery pick
def lotteryPick(M):

    # if M is less than 5, return empty list
    while M < 5:
        empty_list = []
        return empty_list
    
    # otherwise return list of 5 random integers from 1 to M
    return r.sample(range(1, M + 1), 5)

# function to determine the number of trials until getting all five matches
def numFailures(M):

    # establish play again flag
    play_again = True

    # initialize number of trials
    trials = 0

    # while the play again flag is true, run the loop
    while play_again == True:

        actual_drawing = lotteryPick(M)
        Quick_Pick = lotteryPick(M)

        # initial count for number of matches
        count = 0

        # add to count every time an entry matches between the lists
        for num1 in actual_drawing:
            for num2 in Quick_Pick:
                if num1 == num2:
                    count += 1
        # for every round of picks, add one to trials
        trials += 1

        # if the number of matches is 5, set play again to false and return the number of trials
        if count == 5:
            play_again = False
            return trials
        
        # otherwise go through the while loop again
        else:
            play_again = True

# main function to ask the user for input and determine the average number of tickets sold before a ticket with 5 matches was issued
def lottery4():

    # query the user for lottery range and number of trials
    M = int(input('Enter M, the lottery range, 1 to M of the drawing: '))

    while M < 5:
        M = int(input('Enter an integer M greater than or equal to 5: '))

    N = int(input('Enter a number of trials to run the lottery 10^N: '))

    # initialize total tickets counter
    total_tickets = 0

    # for each trial, add to total tickets the number of trials needed until a winning ticket is drawn
    for num in range(10**N):
        total_tickets += numFailures(M)

    # calculate the average by dividing the total tickets by the number of trials
    average = total_tickets/(10**N)

    # print results
    print('Number of trials conducted: ' + str(10**N))
    print('Average tickets sold before winning ticket was issued: ' + str(average))

# run main function
lottery4()
