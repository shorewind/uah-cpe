# esther shore
# egr-101
# homework 4, question 5

# this program simulates multiple trials of a person walking into a room of N people
# and determining if your birthday matches any of the other N people in the room
# number of people varied from 2 to 400 people
# outputs lists for 100 trials, 1000 trials, and 10000 trials

import random as r

# function to determine if there is birthday match in room of N other people as in question 4
def myBirthday(N):
    
    birthday_list = []

    for i in range(N):
        birthday_list.append(r.randint(1, 365))
        
    my_birthday = 150
    
    if my_birthday in birthday_list:
        return True
    return False

# function to determine the proportion of birthday matches after some number of trials
def experiment(N, trials):

    count = 0  # initialize counter

    # for each trial, if a birthday match is found, add 1 to the count
    for m in range(trials):
        if myBirthday(N) == True:
            count += 1

    # calculate the proportion of trials where there is a birthday match
    percentage = count/trials  # percentage expressed as a proportion

    return percentage

# main function to create three lists with varying number of trials, people, and the resulting probability of being my birthday
def main():

    print('My Birthday Program')

    # establish lists for each number of trials used
    list1 = [['Number of People', 'Percentage']]
    list2 = [['Number of People', 'Percentage']]
    list3 = [['Number of People', 'Percentage']]

    # for every number of people, append entry with number of people and percentage to appropriate list
    for N in range(2, 401):
        list1.append([N, experiment(N, 100)])
        list2.append([N, experiment(N, 1000)])
        list3.append([N, experiment(N, 10000)])

    # print results
    print('List 1 (100 trials):')
    print(list1)
    print('List 2 (1000 trials):')
    print(list2)
    print('List 3 (10000 trials):')
    print(list3)


if __name__ == '__main__':
    main()
