# esther shore
# egr-101
# homework 1, question 5

print('This program finds the average of the elements in a list.')

# prompt the user for number of elements

n = int(input('How many elements are in your list? '))

# create list and prompt user for entries
# add each inputted element to list

list1 = []
for index in range(0, n):
    element = float(input('Enter an element: '))
    list1.append(element)

# display given list

print('Your list: ' + str(list1))

# add the elements of the list and divide by the number of elements

print('The average of the elements in the list is ' + str(sum(list1)/n))
