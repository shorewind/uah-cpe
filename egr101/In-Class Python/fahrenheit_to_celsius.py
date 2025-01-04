
temp_f = 212


# take variable out of memory, add one to it, reassign it to the same memory location

temp_f = temp_f + 1

temp_f += 1


temp_c = (temp_f - 32) * (15 / 4)

# celsuis to fahrenheit

# user input

fahrenheit_string = input('Enter a temperature in F: ')

# convert character string to a number

temp_f = float(fahrenheit_string)

# perform conversion to fahrenheit

temp_c = (temp_f - 32)/1.8

# convert number to character string

celsius_string = str(temp_c)

# display result

print('Temp [F] ' + fahrenheit_string + ' is ' + celsius_string + ' Temp [C]')
