/*******************************************************************************************************
// CS317-01 Programming Assignment 1
// March 2024
// Esther Shore
// Program: Merge Sort and Quick Sort Implementation in C++17 (using VSCode with g++ compiler)
// Input: text file containing words separated by whitespace, number of words per line
// Output: text file containing sorted words separated by commas with specified number of words per line
> For your chosen programming language what is involved in comparing two strings? I.E. what does it
cost? Is it a fixed cost per pair of strings?
For C++, comparing two strings involves character-by-character comparison of their corresponding ASCII
code, or Unicode values in the case of special characters, and stopping when either a difference is
found or one of the strings ends. In our program, we wanted the string comparison to be case
insensitive, so there is an additional cost for converting the characters in the strings to lowercase
for comparison. The cost of the string comparison can be characterized by its time complexity, which
is O(n) where n is the length of the shorter string. It is not a fixed cost per pair of strings since
it depends on both the length of the strings as well as the specific characters within the strings,
which determines when the comparison stops if a difference is found before the end of the strings.
********************************************************************************************************/
#include <iostream>
#include <string>
#include <fstream>

using namespace std;            // not good practice but functional

const int MAX_WORDS = 100000;   // set max words to read from file

// function prototypes
int compareStrings(string, string);
void quickSort(string* words, int left, int right);
int partition(string* words, int left, int right);
void mergeSort(string* words, string* temp_words, int left, int right);
void merge (string* words, string* temp_words, int left, int mid, int right);
void displayWords(ofstream& output_file, string* words, int size, int words_per_line, bool reverse);

// main function to get user inputs, call functions, and output to console
int main() {
    string input_file_name;
    string output_file_name;                    // names of files
    ifstream input_file;
    ofstream output_file;                       // input and output file streams
    string word;                                // variable to read input words
    string* words = new string[MAX_WORDS];
    string* temp_words = new string[MAX_WORDS]; // dynamically allocated arrays to store words
    int count = 0;                              // number of words in input file
    int words_per_line;                         // input number of words per line

    cout << "Welcome to the sorting words program." << endl << "Please enter the name of your input data file: ";
    cin >> input_file_name;                     // get input file from user input
    input_file.open(input_file_name.c_str());   // open input file
    if (input_file.fail()) { return 1; }        // return if failed to open

    cout << "Please enter the name of the output data file: ";
    cin >> output_file_name;                    // get output file from user input
    output_file.open(output_file_name.c_str()); // open output file
    if (output_file.fail()) { return 1; }       // return if failed to open
    
    while (input_file >> word && count < MAX_WORDS) {
        words[count++] = word;                  // read words from input file and put into array
    }
    input_file.close();

    cout << endl << count << " words were found in the file: " << input_file_name << "." << endl;
    cout << "How many words per line should be printed? ";
    cin >> words_per_line;                      // get number of words per line from user input
    cout << endl;

    quickSort(words, 0, count - 1);             // perform quicksort on words array from index 0 to count-1

    output_file << count << " words sorted using quicksort:" << endl << endl;
    displayWords(output_file, words, count, words_per_line, false);
    output_file << endl << endl;

    input_file.open(input_file_name.c_str());
    count = 0;
    while (input_file >> word && count < MAX_WORDS) {
        words[count++] = word;                  // retrieve words from input file and reassign words array
    }
    input_file.close();

    mergeSort(words, temp_words, 0, count - 1); // perform mergesort on words array from index 0 to count-1

    output_file << count << " words sorted using mergesort, printed in reverse order:" << endl << endl;
    displayWords(output_file, words, count, words_per_line, true);

    output_file.close();

    delete[] temp_words;
    delete[] words;                             // deallocate word arrays

    cout << "End program." << endl;
    return 0;
}

int compareStrings(string word1, string word2) {
    // use copies of words to not affect the resulting appearance in sorted array
    string word1_copy = word1;
    string word2_copy = word2;

    // max number of characters to compare is equal to length of shorter word
    int num_chars = min(word1_copy.length(), word2_copy.length());

    // convert each character of each word to lowercase
    for (int i = 0; i < num_chars; i++) {
        word1_copy[i] = tolower(word1_copy[i]);
        word2_copy[i] = tolower(word2_copy[i]);
    }

    // string comparisons
    if (word1_copy < word2_copy) { return -1; }
    else if (word1_copy > word2_copy) { return 1; }

    // if comparisons are equal, then base off word length
    if (word1.length() == word2.length()) { return 0; }
    else { return word1.length() < word2.length() ? -1 : 1; }
}

void quickSort(string* words, int left, int right) {
    if (left < right) {
        // get split position for partitition
        int split_pos = partition(words, left, right);
        // sort each half of partitition
        quickSort(words, left, split_pos - 1);
        quickSort(words, split_pos + 1, right);
    }
}

int partition(string* words, int left, int right) {
    // assign pivot word to compare against and indices
    string pivot = words[left];
    int i = left;
    int j = right;

    // while the left index is less than or equal to the right index
    while (i <= j) {
        // increment i until words[i] > pivot
        while (i <= right && compareStrings(words[i], pivot) <= 0) { 
            i++;
        }
        // increment j until words[j] <= pivot
        while (j > left && compareStrings(words[j], pivot) > 0) {
            j--;
        }
        if (i < j) {
            swap(words[i], words[j]);   // don't swap when i >= j
            i++;
            j--;
        }
    }
    swap(words[left], words[j]);        // swap pivot with words[j]
    return j;                           // return index j
}

void mergeSort(string* words, string* temp_words, int left, int right) {
    if (left < right) {
        // get midpoint index
        int mid = left + (right - left) / 2;
        // perform recursive mergesort on each side
        mergeSort(words, temp_words, left, mid);
        mergeSort(words, temp_words, mid + 1, right);
        // merge together sorted sides
        merge(words, temp_words, left, mid, right);
    }
}


void merge(string* words, string* temp_words, int left, int mid, int right) {
    // get reference indices
    int i = left;
    int j = mid + 1;
    int k = left;

    // merge two sorted arrays into temp_words
    while (i <= mid && j <= right) {
        // if words[i] <= words[j], put words[i] into sorted array and increment i
        if (compareStrings(words[i], words[j]) <= 0) {  // < would produce an unstable implementation as shown in the assignment example
            temp_words[k++] = words[i++];
        } else {  // otherwise put words[j] into sorted array and increment j
            temp_words[k++] = words[j++];
        }
    }

    // copy remaining elements from each side to temp_words
    while (i <= mid) {
        temp_words[k++] = words[i++];
    }
    while (j <= right) {
        temp_words[k++] = words[j++];
    }

    // copy elements from temp_words back to words
    for (int l = left; l <= right; l++) {
        words[l] = temp_words[l];
    }
}

void displayWords(ofstream& output_file, string* words, int size, int words_per_line, bool reverse) {
    int max_word_length = 0;

    // find the length of the longest word
    for (int i = 0; i < size; i++) {
        int word_length = words[i].length();
        if (word_length > max_word_length) {
            max_word_length = word_length;
        }
    }

    // if reverse == true then display words in reverse order
    if (reverse) {
        for (int i = size - 1; i >= 0; i--) {
            output_file << right << setw(max_word_length + 1) << words[i] << ",";
            if ((size - i) % words_per_line == 0) {
                output_file << endl;    // add newline every set words per line
            }                           // set width based on max word length found
        }
    } else {
        for (int i = 0; i < size; i++) {
            output_file << right << setw(max_word_length + 1) << words[i] << ",";
            if ((i + 1) % words_per_line == 0) {
                output_file << endl;
            }
        }
    }
}

//end of code xoxoxo
