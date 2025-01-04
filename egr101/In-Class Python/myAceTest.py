# in-class assignment
# find the first ace dealt

ACE_H = 0
ACE_S = 13
ACE_D = 26
ACE_C = 39

import random as r

def aceTest(N):

    location = 0  # where i find the aces
    
    for idx in range(0, N):
        shuffleDeck = r.sample(range(52), 52)
        
        aceLocation = []
        aceLocation.append(shuffleDeck.index(ACE_H))
        aceLocation.append(shuffleDeck.index(ACE_S))
        aceLocation.append(shuffleDeck.index(ACE_D))
        aceLocation.append(shuffleDeck.index(ACE_C))

        aceLocation.sort()
        location += aceLocation[0]

    return(location/N)

EXACT = 48/5

def main():

    N_trial = 1

    while abs(aceTest(N_trial)-EXACT) > 0.01:
        N_trial += 1
        
    print(N_trial)
