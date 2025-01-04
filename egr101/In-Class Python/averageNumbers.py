# inclass average number example (HW 3.1)
# esther shore
# egr-101


print('This program calculates the average number of a list that you enter.')

# query the user for the number of elements in their list

N = int(input('What is the length of your list ?'))


# list to be formed

myList = []

for num in range(0,N):
    element = float(input('Enter an element of the list: '))
    myList.append(element)


print('The average value of the list elements is ' + str(sum(myList)/N))
