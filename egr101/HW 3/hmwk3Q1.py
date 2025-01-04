# esther shore
# egr-101
# homework 3, question 1

# display prompt function

def display_prompt():
    print('This program accepts an integer and determines if the integer is a power of two.')

# establish function to determine if an integer is a power of two

def is_power_of_two(n):
    if n == 0:
        return False
    while n > 0:
        if n == 1:
            return True
        elif n % 2 != 0:
            return False
        else:
            n = n / 2
    return True
        
# establish main function

def main():
    display_prompt()  # call display prompt function

    # query the user
    
    N = int(input('Enter an integer: '))

    # call function to determine if an integer is a power of two
    # print result for each case
    
    if is_power_of_two(N):
        print(str(N) + ' is a power of two.')
    else:
        print(str(N) + ' is not a power of two.')

# run main function

if __name__ == '__main__':
    main()

        
