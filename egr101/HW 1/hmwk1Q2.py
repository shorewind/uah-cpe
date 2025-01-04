# esther shore
# egr-101
# homework 1, question 2

print('This program takes a list and removes the duplicate items from the list.')

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

# establish new list
# append elements not already in new list

list2 = []
for element in list1:
    if element not in list2:
        list2.append(element)

# display new list

print('Your new list: ' + str(list2))
