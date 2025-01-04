# esther shore
# egr-101
# homework 1, question 1

print('This program swaps the first and last element of a list and displays the newly-formed list.')

# prompt the user for number of elements

n = int(input('How many elements are in your list? '))

# create list and prompt user for entries
# add each inputted element to list

list1 = []
for index in range(0, n):
    element = input('Enter an element: ')
    list1.append(element)

# display given list

print('Your list: ' + str(list1))

# switch first and last elements
# use temporary variable

temp = list1[0]
list1[0] = list1[-1]
list1[-1] = temp

# display new list

print('Your new list: ' + str(list1))
