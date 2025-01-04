# hw 7.1
# investment calculator

invest = float(input('Enter an amount you seek to save per month: '))
endAmount = float(input('Enter an amount you want at the end: '))

# investment return

rate = 0.07/12  # seven percent

# number of months that gets computed in the while loop

N = 0

# my nest egg

total = 0

while total < endAmount:
    interest = total * rate
    total += invest + interest
    N += 1

roundedTotal = round(total*100)/100
print('After ' + str(N) + ' months you will have $' + str(roundedTotal))
