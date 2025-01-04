# investment calculator

# repeated investment each month for a period of time

invest = float(input('Enter an amount you seek to save per month: '))

# investment return

rate = 0.07/12  # seven percent

# number of months

N = int(input('Enter number of months: '))

# my nest egg

total = 0

for n in range(0, N + 1):
    interest = total * rate
    total += invest + interest

roundedTotal = round(total*100)/100
print('After ' + str(N) + ' months you will have $' + str(roundedTotal))
