# esther shore
# egr-101
# homework 1, question 4

print('This program takes a list and prints the second largest number in the list.')

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

# sort the list in ascending order

list1.sort()

# identify and print the second largest number in the list

print('The second largest number is ' + str(list1[n-2]))
