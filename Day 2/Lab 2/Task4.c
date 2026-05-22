#include <stdio.h>
#include <math.h>
#include <time.h>

int main() {
    int number;       // Current number being tested
    int divisor;      // Number used to test divisibility
    int isPrime;      // 1 means prime, 0 means not prime
   

    double limit;     // Square root of the current number

    clock_t startTime;    // Time before the calculation starts
    clock_t endTime;      // Time after the calculation ends
    double elapsedSec;    // Elapsed time in seconds

    // Start timing
    startTime = clock();

    // Check each number from 1 to 100
    for (number = 1; number <= 100; number++) {

        // Assume the number is prime first
        isPrime = 1;

        // Numbers less than 2 are not prime
        if (number < 2) {
            isPrime = 0;
        }

        // 2 is prime
        else if (number == 2) {
            isPrime = 1;
        }

        // Even numbers greater than 2 are not prime
        else if (number % 2 == 0) {
            isPrime = 0;
        }

        // Check odd numbers greater than 2
        else {
            // Stop checking at the square root
            limit = sqrt(number);

            // Start with the first odd divisor
            divisor = 3;

            // Only check odd divisors up to the square root
            while (divisor <= limit) {
                if (number % divisor == 0) {
                    isPrime = 0;
                    break;
                }

                divisor = divisor + 2;
            }
        }

        // Print the number if it is prime
        if (isPrime == 1) {
            printf("%d\n", number);
        }
    }

    // End timing
    endTime = clock();

    // Convert clock ticks to seconds
    elapsedSec = ((double)(endTime - startTime)) / CLOCKS_PER_SEC;

    printf("Time used: %f seconds\n", elapsedSec);

    return 0;
}