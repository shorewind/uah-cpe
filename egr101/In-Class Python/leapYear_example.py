# leap year

year  = int(input('Enter a Year to Determine Leap Year : '))


if year % 4 != 0 :
	isPrime = False
else:
	if year % 100 != 0:
		isPrime = True
	else:
		if year % 400 == 0:
			isPrime = True
		else:
			isPrime = False

print(isPrime)

