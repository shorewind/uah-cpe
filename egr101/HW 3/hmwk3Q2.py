# esther shore
# egr-101
# homework 3, question 2

# create display prompt

def display_prompt():
    print('This program accepts an integer N and determines the number of prime numbers between 2 and N.')

# function to determine if number is prime

def is_prime(n):
    # if n has a factor other than itself and 1, then it is not prime
    for num in range(2, n):
        if n % num == 0:
            return False
    return True

# create main function

def main():
    display_prompt()  # call display prompt
    N = int(input('Enter an integer: '))  # query the user
    total = 0  # establish total count variable

    # iterate through numbers in range and add to count if it is prime
    
    for i in range(2, N + 1):
        if is_prime(i) == True:
            total += 1

    # print result
    
    print('There are ' + str(total) + ' prime numbers between 2 and ' + str(N))

# run main function

if __name__ == "__main__":
    main()
