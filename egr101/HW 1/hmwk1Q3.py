# esther shore
# egr-101
# homework 1, question 3

print('This program merges two lists, sorts the merged list, and displays the merged list.')

# prompt the user for number of elements

n1 = int(input('How many elements are in your first list? '))

# create list and prompt user for entries
# add each inputted element to list

list1 = []
for index in range(0, n1):
    element = input('Enter an element: ')
    list1.append(element)

# display given list

print('Your first list: ' + str(list1))


# again for second list


# prompt the user for number of elements

n2 = int(input('How many elements are in your second list? '))

# create list and prompt user for entries
# add each inputted element to list

list2 = []
for index in range(0, n2):
    element = input('Enter an element: ')
    list2.append(element)  # appending to list1 would be more concise

# display given list

print('Your second list: ' + str(list2))

# append elements from second list to first list

for element in list2:
    list1.append(element)

# sort the merged list

list1.sort()

# display new list

print('Your new list: ' + str(list1))
