#include <stdio.h>
#include <time.h>

int main() {
    
    char s[100];
    // Store the time when the program starts.
    time_t start = time(NULL);

    // In this assignment:
    // F(0) = 1 and F(1) = 1.
    long long beforePrevious = 1;
    long long previous = 1;
    long long current = 1;

    int n = 1;
    int highestN = 1;
    long long highestValue = 1;

    // Keep running until 5 seconds have passed.
    while (time(NULL) - start < 5) {

        // Calculate the next Fibonacci number.
        current = previous + beforePrevious;

        // Move the old values forward.
        beforePrevious = previous;
        previous = current;

        // Move to the next index.
        n++;

        // Save the highest Fibonacci number found so far.
        highestN = n;
        highestValue = current;
    }

    // Print only the highest Fibonacci number found after 5 seconds.
    printf("The highest Fibonacci number found was F(%d) = %lld\n", highestN, highestValue);
    
    fgets(s, 100, stdin);
    return 0;
}