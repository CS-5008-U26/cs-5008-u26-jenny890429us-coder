#include <stdio.h>

// printPrimeFactors
// Prints the prime factors of a number in order from smallest to largest.
// Parameters:
//     int number    the number being factored
// Returns:
//     Nothing. This function prints the factors directly.
//
// Example:
//     printPrimeFactors(180) prints 2 * 2 * 3 * 3 * 5
void printPrimeFactors(int number) {

    // Base case:
    // If number is 1, there are no more prime factors to print.
    if (number == 1) {
        return;
    }

    // Start testing possible factors at 2,
    // because 2 is the smallest prime factor.
    int factor = 2;

    // Find the smallest factor of number.
    // Keep increasing factor until it divides number evenly.
    while (number % factor != 0) {
        factor++;
    }

    // Print the factor we found.
    printf("%d", factor);

    // Remove this factor from number.
    // The remaining number may still have more prime factors.
    number = number / factor;

    // Print the separator only if more factors remain.
    // This prevents a " * " after the last factor.
    if (number > 1) {
        printf(" * ");
    }

    // Recursive call:
    // Continue printing the prime factors of the remaining number.
    printPrimeFactors(number);
}

int main() {


    char s[100];

    // Store the number entered by the user.
    int number;

    // Ask the user for a number.
    printf("Enter a number: ");

    // Read the number from the user.
    scanf("%d", &number);

    // Clear the newline character left in the input buffer after scanf.
    fgets(s, 100, stdin);

    // Print the beginning of the output line.
    printf("The prime factors are ");

    // Call the recursive function to print the factors.
    printPrimeFactors(number);

    // End the output line.
    printf("\n");

    // Pause the program so the output window stays open on Windows.
    fgets(s, 100, stdin);

    return 0;
}