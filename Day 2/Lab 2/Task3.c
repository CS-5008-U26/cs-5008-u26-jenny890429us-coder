#include <stdio.h>
#include <time.h>

/*
 * This program prints all prime numbers up to 100.
 * It uses the simple method of trying every divisor
 * from 2 to one less than the number itself.
 * It also prints the elapsed time.
 */
int main() {
    int number;       // The current number we are checking
    int divisor;      // The number we try to divide by
    int isPrime;      // 1 means prime, 0 means not prime

    clock_t startTime;    // Time before the calculation starts
    clock_t endTime;      // Time after the calculation ends
    double elapsedSec;    // Elapsed time in seconds

    // Start timing
    startTime = clock();

    // Check every number from 2 to 100
    for (number = 2; number <= 100; number = number + 1) {
        isPrime = 1;  // Assume the number is prime first

        // Try every divisor from 2 to number - 1
        for (divisor = 2; divisor < number; divisor = divisor + 1) {
            if (number % divisor == 0) {
                isPrime = 0;  // If divisible, it is not prime
                break;        // Stop checking this number
            }
        }

        // If the number is still marked as prime, print it
        if (isPrime == 1) {
            printf("%d\n", number);
        }
    }

    // Stop timing
    endTime = clock();

    // Convert clock ticks to seconds
    elapsedSec = (double)(endTime - startTime) / CLOCKS_PER_SEC;

    printf("Elapsed time: %f seconds\n", elapsedSec);

    return 0;
}