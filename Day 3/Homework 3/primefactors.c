#include <stdio.h>

int main() {

    char s[100];

    // Store the number entered by the user.
    int number;

    // factor is the number we are currently testing as a factor.
    // We start with 2 because 2 is the smallest prime factor.
    int factor = 2;

    // first keeps track of whether we are printing the first factor.
    // This helps us print " * " only between factors.
    int first = 1;

    // Ask the user for a number.
    printf("Enter a number: ");

    // Read the number from the user.
    scanf("%d", &number);

    // Clear the newline character left in the input buffer after scanf.
    fgets(s, 100, stdin);

    // Print the beginning of the output line.
    printf("The prime factors are ");

    // Keep factoring until number becomes 1.
    // When number is 1, all prime factors have been removed.
    while (number > 1) {

        // If factor divides number evenly, then factor is one prime factor.
        if (number % factor == 0) {

            // Print the factor.
            // Do not print " * " before the first factor.
            if (first) {
                printf("%d", factor);
                first = 0;
            } else {
                printf(" * %d", factor);
            }

            // Divide number by this factor.
            // This removes one copy of factor from number.
            number = number / factor;
        } else {

            // If factor does not divide number,
            // try the next possible factor.
            factor++;
        }
    }

    // End the output line.
    printf("\n");

    // Pause the program so the output window stays open on Windows.
    fgets(s, 100, stdin);

    return 0;
}