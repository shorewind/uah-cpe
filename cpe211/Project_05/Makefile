# by listing names on the program line, Make will run the commands
# for each of the names listed.  In this case make will create
# Project_05 and run clean.  Execution is in the order of the 
# list from left to right.  remove clean from the program line
# if you want to make the user explicitly run the clean command
# which is done by typing make clean at a prompt.

program: Project_05
#program: Project_05 clean

# if it is desired to only run clean when we demand it,
# then take clean off of the program line:
# program: Project_05

# The following is used if there is a single file only
# that needs to be compiled
#Project_05 : Project_05.cpp
#	g++ -std=c++11 Project_05.cpp -o Project_05

# the following commands are used to compile and link
# programs that contain 2 or more source code files
# all source code files are used to create their object(.o)
# files and then all of the .o files are compiled to
# obtain the executable.  This procedure is what is needed
# for Projects in CPE212, so we will use it even if
# we only have 1 file to compile

Project_05 : Project_05.o
	g++ -std=c++11 -Wall Project_05.o -o Project_05

Project_05.o : Project_05.cpp
	g++ -std=c++11 -Wall -c Project_05.cpp 

# clean will remove all the object files created
# could remove clean from the program list and 
# add the name of the executable to the list
# of what to remove: rm *.o Project_05
cleanAll : 
	rm *.o Project_05
clean :
	rm *.o
