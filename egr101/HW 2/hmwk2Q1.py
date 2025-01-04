# esther shore
# egr-101
# homework 2, question 1

print('This program accepts three distinct digits from a user and prints all possible combinations from the digits.')

# create list

list1 = []

# query the user and add each integer to list

num1 = int(input('Enter an integer: '))
list1.append(num1)
num2 = int(input('Enter an integer: '))
list1.append(num2)
num3 = int(input('Enter an integer: '))
list1.append(num3)

# show digits in list

print('Your digits:')
print(list1)


# combinations

print('Possible combinations:')

# iterate through each index of list
# print result if indexes are not the same

for i in range(3):
    for j in range(3):
        for k in range(3):
            if i != j and j != k and i != k:
                print(list1[i], list1[j], list1[k])
