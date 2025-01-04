import travelTime as t

# function to display what the program does
def displayPrompt():
    print('Time Travel Calculator')

# another program that uses the function

def main():
    displayPrompt()  # there are no variables being passed
    KM2METERS = 1000  # variable that doesn't change
    runAgainFlag = True
    while runAgainFlag == True:

        dist_km = float(input('Enter a distance in km: '))
        speed_mps = float(input('Enter a speed in m/s: '))
        dist_m = dist_km * KM2METERS
        print('The travel time in seconds is ' + str(t.travelTime(dist_m, speed_mps)))

        userString = input('Run again [y/n] ')

        if userString.lower() != 'y':
            runAgainFlag = False
        else:
            runAgainFlag = True

    print('Good bye')

if __name__ == "__main__":
    main()
        
