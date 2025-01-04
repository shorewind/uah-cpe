# anyBirthdayExperiment
# in next homework yourBirthday

def has_duplicates(values):
    for idx in range(len(values)):
        for jdx in range(idx + 1, len(values)):
            if values[idx] == values[jdx]:
                return True
    return False


import random as r

# runs the birthday experiment once with N people
def anyBirthday(N):

    peopleBirth = []  # list to store birthdays
    for n in range(N):
        peopleBirth.append(r.randint(1, 365))  # place a random birthday here
    if has_duplicates(peopleBirth) == True:  # we need to find a function
        return True
    else:
        return False

def experiment(N):  # runs the experiment with N people 100 times

    nTrials = 100
    count = 0
    for n in range(nTrials):
        if anyBirthday(N) == True:
            count += 1

    return count/nTrials

import csv

def main():
    nPeople = 100
    probData = [['People', 'Percent']]

    for idx in range(2, nPeople + 1):
        data = []
        data.append(idx)
        data.append(experiment(idx))
        probData.append(data)
    print(probData)

    with open('birthProb.csv', 'w', newline = '') as file:
        writer = csv.writer(file)
        writer.writerows(probData)

if __name__ == '__main__':
    main()
