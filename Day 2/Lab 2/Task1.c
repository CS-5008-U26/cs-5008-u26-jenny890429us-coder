#include <stdio.h>

/*
 * This program asks the user to enter a number.
 * It calculates and prints the sum of all digits in that number.
 */
int main() {
    int number;     // The number entered by the user
    int digit;      // The current rightmost digit of the number
    int sum = 0;    // The total sum of the digits

    // Ask the user to enter a number
    printf("Enter a number: ");
    scanf("%d", &number);

    // Repeat while there are still digits left in the number
    while (number > 0) {
        digit = number % 10;      // Get the rightmost digit
        sum = sum + digit;        // Add the digit to the total sum
        number = number / 10;     // Remove the rightmost digit
    }

    // Print the final sum of the digits
    printf("The sum of the digits is %d\n", sum);

    return 0;
}