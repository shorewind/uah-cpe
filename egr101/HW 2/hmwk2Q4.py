# esther shore
# egr-101
# homework 2, question 4

print('This program takes a dictionary and multiplies all the items in the dictionary.')
print('(multiplies the values together)')

# given dictionary

d = {'A':70,'B':14,'C':23}

print('Dictionary:')
print(d)

# create variable to store result

total = 1

# multiply values using for loop

for value in d.values():
    total *= value

# print result

print('The total is: ' + str(total))


# version 2

print('This program takes a dictionary and multiplies all the items in the dictionary.')
print('(multiples the values by a given integer)')

# query the user

n = int(input('Enter an integer: '))

# multiply each value by the integer

for value in d:
    d[value] *= n

# print result

print('New dictionary: ')
print(d)
