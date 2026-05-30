#include <stdio.h>

// complement
// Calculates the 10's complement of an integer.
// Parameters:
//     int x    the integer being complemented
// Returns:
//     int      the 10's complement of x
//
// Example:
//     complement(123) returns 876
int complement(int x) {

    // Base case:
    // If x has only one digit, its complement is simply 9 - x.
    if (x < 10) {
        return 9 - x;
    }

    // Get the rightmost digit of x.
    // Example: if x is 12345, rightDigit is 5.
    int rightDigit = x % 10;

    // Remove the rightmost digit from x.
    // Example: if x is 12345, leftPart is 1234.
    int leftPart = x / 10;

    // Recursive case:
    // First compute the complement of the left part.
    // Then multiply by 10 to make room for the new rightmost digit.
    // Finally add the complement of the original rightmost digit.
    //
    // Example:
    // complement(123)
    // = complement(12) * 10 + (9 - 3)
    // = 87 * 10 + 6
    // = 876
    return complement(leftPart) * 10 + (9 - rightDigit);
}

int main() {

    char s[100];

    // Store the number entered by the user.
    int number;

    // Ask the user for an integer.
    printf("Enter an integer: ");

    // Read the integer from the user.
    scanf("%d", &number);

    // Clear the newline character left in the input buffer after scanf.
    fgets(s, 100, stdin);

    // Call the recursive function and print the result.
    printf("The complement is %d\n", complement(number));

    // Pause the program so the output window stays open on Windows.
    fgets(s, 100, stdin);

    return 0;
}