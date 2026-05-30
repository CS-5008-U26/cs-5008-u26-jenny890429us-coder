#include <stdio.h>
#include <time.h>

// fibonacci
// Calculates the nth Fibonacci number recursively.
// In this assignment, F(0) = 1 and F(1) = 1.
//
// Parameters:
//     int n    the index of the Fibonacci number
// Returns:
//     long long    the nth Fibonacci number
long long fibonacci(int n) {

    // Base case:
    // F(0) = 1 and F(1) = 1.
    if (n < 2) {
        return 1;
    }

    // Recursive case:
    // F(n) = F(n - 1) + F(n - 2).
    return fibonacci(n - 1) + fibonacci(n - 2);
}

int main() {

    // Store the time when the program starts.
    time_t start = time(NULL);

    int n = 0;
    int highestN = 0;
    long long highestValue = 0;

    // Keep running until 5 seconds have passed.
    while (time(NULL) - start < 5) {

        // Calculate the nth Fibonacci number.
        long long value = fibonacci(n);

        // Save the highest Fibonacci number found so far.
        highestN = n;
        highestValue = value;

        // Move to the next Fibonacci number.
        n++;
    }

    // Print only the highest Fibonacci number found after 5 seconds.
    printf("The highest Fibonacci number found was F(%d) = %lld\n", highestN, highestValue);

    return 0;
}