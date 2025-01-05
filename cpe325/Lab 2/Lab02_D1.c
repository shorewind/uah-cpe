/*------------------------------------------------------------------------------
* File: Lab02_D1.c
* Function: Prints decimal, hex, and octal representations of numbers
* Description: This program demonstrates common C data types and
* printf formatting options.
* Input: None
* Output: Console print statements
* Author(s): Aleksandar Milenkovic, milenkovic@computer.org
* Date: Aug 16, 2017
* ---------------------------------------------------------------------------*/
#include <msp430.h>
#include <stdio.h>
#include <limits.h>
#include <float.h>

int main(void)
{
    WDTCTL = WDTPW + WDTHOLD; // Stop watchdog timer
    printf("Data Type              | Size (in bytes)\t| Minimum\t\t| Maximum\n");
    printf("char                   | %d\t\t\t| %d\t\t\t| %d\n", sizeof(char), CHAR_MIN, CHAR_MAX);
    printf("short int              | %d\t\t\t| %d\t\t| %d\n", sizeof(short int), SHRT_MIN, SHRT_MAX);
    printf("int                    | %d\t\t\t| %d\t\t| %d\n", sizeof(int), INT_MIN, INT_MAX);
    printf("long int               | %d\t\t\t| %ld\t\t| %ld\n", sizeof(long int), LONG_MIN, LONG_MAX);
    printf("unsigned int           | %d\t\t\t| %d\t\t\t| %u\n", sizeof(unsigned int), 0, UINT_MAX);
    printf("unsigned long int      | %d\t\t\t| %d\t\t\t| %ul\n", sizeof(unsigned long int), 0, ULONG_MAX);
    printf("long long int          | %d\t\t\t| %lld\t| %lld\n", sizeof(long long int), LLONG_MIN, LLONG_MAX);
    printf("unsigned long long int | %d\t\t\t| %d\t\t\t| %llu\n", sizeof(unsigned long long int), 0, ULLONG_MAX);
    printf("float                  | %d\t\t\t| %ld\t\t| %ld\n", sizeof(float), -FLT_MAX, FLT_MAX);
    printf("double                 | %d\t\t\t| %ld\t\t\t| %ld\n", sizeof(int), -DBL_MAX, DBL_MAX);
    return 0;
}
