# square number dictionary

# accept an integer from a user entry

N = int(input('Enter an integer: '))

# form a dictionary

sqNumDictionary = {x:x*x for x in range(1,N+1)}

print(sqNumDictionary)
