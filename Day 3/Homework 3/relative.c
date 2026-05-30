#include <stdio.h>

// et
// Calculates the ET-function for x.
// The ET-function is the number of integers less than x
// that are relatively prime with x.
//
// Two numbers are relatively prime if they have no common factors
// other than 1.
//
// Parameters:
//     int x    the number being examined
// Returns:
//     int      the number of integers less than x that are relatively prime with x
int et(int x) {

    // count stores how many numbers less than x are relatively prime with x.
    int count = 0;

    // Check every integer i from 1 to x - 1.
    // These are the numbers less than x.
    for (int i = 1; i < x; i++) {

        // Assume i and x are relatively prime at first.
        // 1 means true, 0 means false.
        int relativelyPrime = 1;

        // Check whether i and x have a common factor other than 1.
        // We start at 2 because 1 is allowed as a common factor.
        for (int d = 2; d <= i; d++) {

            // If d divides both x and i evenly,
            // then d is a common factor of x and i.
            if ((x % d == 0) && (i % d == 0)) {

                // Since they have a common factor other than 1,
                // they are not relatively prime.
                relativelyPrime = 0;
            }
        }

        // If no common factor was found,
        // then i and x are relatively prime.
        if (relativelyPrime) {
            count++;
        }
    }

    // Return the total number of integers less than x
    // that are relatively prime with x.
    return count;
}

int main() {

    char s[100];

    // Store the integer entered by the user.
    int n;

    // Ask the user for an integer.
    printf("Enter an integer: ");

    // Read the integer from the user.
    scanf("%d", &n);

    // Clear the newline character left in the input buffer after scanf.
    fgets(s, 100, stdin);

    // Print the ET-function for every integer from 2 to n.
    for (int i = 2; i <= n; i++) {
        printf("et(%d) = %d\n", i, et(i));
    }

    // Pause the program so the output window stays open on Windows.
    fgets(s, 100, stdin);

    return 0;
}