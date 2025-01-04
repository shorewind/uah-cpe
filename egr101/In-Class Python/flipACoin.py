# simulate flipping a coin

import random as r

def flipACoin():
    """ returns 0 if tails, 1 if heads """  # provides help message
    if r.randint(1,2) == 2:
        return(1)
    else:
        return(0)

# main program to flip a coin a thousand times

def main():
    N_Trials = 1000

    count = 0  # counter for the number of heads

    for n in range(0, N_Trials):
        if flipACoin() == 1:
            count += 1
    print('Number of heads: ' + str(count))
