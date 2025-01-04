# esther shore
# egr-101
# homework 4, question 4

# this program simulates a single trial of a person walking to a room of N people
# determines if my birthday matches any of the other N people in the room

import random as r

# function to determine if my birthday matches that of anyone in a room of N people
def myBirthday(N):
    
    birthday_list = []  # establish list of birthdays

    # for each of N people in room, generate random integer representing their birthday and add to list
    for i in range(N):
        birthday_list.append(r.randint(1, 365))

    my_birthday = 150  # my birthday as a day out of 365, could ask for user input

    # search for my_birthday in birthday_list and determine and return appropriate boolean value
    if my_birthday in birthday_list:
        return True
    return False

# main function to accept integer from user and display result
def main():

    print('My Birthday Function')
    
    # query the user
    N = int(input('Enter an integer N for the number of other people in the room: '))

    # print results for the corresponding scenario
    if myBirthday(N) == True:
        print('In the room of ' + str(N) + ' other people, you have a birthday match!')
    else:
        print('In the room of ' + str(N) + ' other people, you do not have a birthday match.')


if __name__ == '__main__':
    main()
            
        
