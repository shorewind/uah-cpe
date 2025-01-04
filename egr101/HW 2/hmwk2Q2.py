# esther shore
# egr-101
# homework 2, question 2

print('This program accepts an integer from a user and tabulates the sum from the first N integers.')

# query the user

N = int(input('Enter an integer: '))

# establish total variable

total = 0

# create new string starting with 1

new_string = ''

# sum numbers and add characters to new string

for num in range(1, N + 1):
    total += num
    if num == N:
        new_string += str(num)
    else:
        new_string += str(num) + ' + '

# print result

print(new_string + ' = ' + str(total))

