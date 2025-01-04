# esther shore
# egr-101
# homework 5, question 1

import random as r

# function to generate list with 5 random integers representing lottery pick
def lotteryPick(M):

    # if M is less than 5, return empty list
    while M < 5:
        empty_list = []
        return empty_list
    
    # otherwise return list of 5 random integers from 1 to M
    return r.sample(range(1, M + 1), 5)

# main function to ask user for input, determine number of matches, and ask to play again
def lottery(): 

    # query the user
    M = int(input('Enter M, the lottery range, 1 to M of the drawing: '))

    # query the user again if input is below 5
    while M < 5:
        M = int(input('Enter an integer M greater than or equal to 5: '))
        
    # establish play again flag
    play_again = 'y'

    # while the user wants to play again, run the loop
    while play_again.lower() == 'y': 

        # call lotteryPick(M) function to create and print drawings for lotterypick and quick pick
        actual_drawing = lotteryPick(M)
        print(actual_drawing)
        Quick_Pick = lotteryPick(M)
        print(Quick_Pick)

        # initialize counter for number of matches found between the picks
        count = 0

        # determine if there are any matching entries and add to count if so
        for num1 in actual_drawing:
            for num2 in Quick_Pick:
                if num1 == num2:
                    count += 1
        print(count)

        # print results
        if count == 1:
            print('Winner: One Match Found')
        elif count > 1:
            print('Winner: ' + str(count) + ' Matches Found')
        else:
            print('Loser: No Matches in Game')

        # prompt the user to play again
        play_again = input('Do you want to play the lottery again? (y/n) ')

    # once play again flag is not equal to y, print logout
    print('logout')
                    
# run main function
lottery()
    
