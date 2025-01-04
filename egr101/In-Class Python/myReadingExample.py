# reading my pi file

with open('pi.txt') as file:
    contents = file.read()
    print(len(contents))

list1 = []

for i in range(len(contents)):
    if contents[i:i+3] == '123':
        list1.append(i)
        list1.append(i+1)
        list1.append(i+2)
    else:
        i+=1
print(list1)
