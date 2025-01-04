% define the binary input sequence
binary_sequence = [0 1 0 1 0 1 0 1 1 1 1 1 0 0 0 1 1 0 1 1];
% time steps corresponding to the binary values
time_steps = [0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19];
% combine the time and binary values into one data matrix
data = [time_steps' binary_sequence'];

