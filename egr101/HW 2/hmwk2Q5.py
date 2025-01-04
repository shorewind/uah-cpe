# esther shore
# egr-101
# homework 2, question 5

print('This pogram takes a string and replaces every blank space with a hyphen.')

# query the user

string = input('Enter a string: ')

# go through each index of string and replace spaces with hyphens
# create new string and add new characters

new_string = ''

for character in string:
    if character == ' ':
        character = '-'
    new_string += character
    
# method using .replace() function

# for i in range(len(string)):
    # string = string.replace(' ','-')

# print new string

print('New string: ' + new_string)
