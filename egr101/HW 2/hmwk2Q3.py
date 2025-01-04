# esther shore
# egr-101
# homework 2, question 3

print('This program tabulates the sum of the series 1 + 1/2 + 1/3 + ... 1/N.')

# query the user

N = int(input('Enter the number of terms N: '))

# declare sum variable

total = 0

# for loop to establish each term and add it to the total
        
for n in range(1, N + 1):
    total += 1 / n

# print result

print('The sum of the series is: ' + str(total))
