#include <stdio.h>

// mark multiples of p as not prime
void EliminateMultiples(int prime_flags[], int n, int p) {
    // increment through multiples between p^2 to n
    for (int i = p * p; i <= n; i += p)  // i in R3, n on stack
        prime_flags[i-1] = 0;  // prime_flags pointer in R0
}

// return result array of primes less than or equal to n
void SieveOfEratosthenes(int n, int *result) {
    int prime_flags[n];  // in memory: FILL 2164, 1, 4  (541*4 = 2164), pointer stored in R0
    int i;  // R3

    // initialize flags to 1, handled by FILL
    for (i = 1; i < n; i++) {
        prime_flags[i] = 1;
    }
 
    // check numbers 1 to sqrt(n) rounded up
    for (int p = 1; p * p <= n; p++) {  // store p in R1, R2 for p*p, n on stack
        // if number flagged, eliminate its multiples
        if (prime_flags[p-1] == 1) {  // prime_flags pointer in R0
            EliminateMultiples(prime_flags, n, p);  // n on stack
        }
    }
 
    // reset counter for reuse
    i = 0;  // R3
    // add prime numbers to result array
    for (int p = 1; p <= n; p++) {  // R1 = p
        if (prime_flags[p-1] == 1) {  // R0 = prime_flags address
            result[i++] = p;  // R2 = result address
            printf("%d ", p);
        }
    }
}
 
int main() {
    int n = 541; // DCD, store on stack
    int result[100];   // SPACE 400
    SieveOfEratosthenes(n, &result[0]);
    return 0;
}
