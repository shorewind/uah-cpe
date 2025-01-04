# get a year from user

year = int(input('Enter a year: '))

isPrime = False;  # flag logical value T/F

if year % 4 != 0:  # is the year divisible by 4
    isPrime = False  # left branch of the logic diagram
else:  # right branch
    if year % 100 != 0:  # right branch
        isPrime = True
    else:
        if year % 400 == 0:  # bottom
            isPrime = True
        else:
            isPrime = False

print(isPrime)
