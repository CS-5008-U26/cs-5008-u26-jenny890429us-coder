#include <stdio.h>

int main() {
    int cents;      // Total number of cents entered by the user
    int quarters;   // Number of quarters needed
    int dimes;      // Number of dimes needed
    int nickels;    // Number of nickels needed
    int pennies;    // Number of pennies needed

    // Ask the user for the number of cents
    printf("Enter a number of cents: ");
    scanf("%d", &cents);

    // Find the number of quarters
    quarters = cents / 25;
    cents = cents % 25;

    // Find the number of dimes
    dimes = cents / 10;
    cents = cents % 10;

    // Find the number of nickels
    nickels = cents / 5;
    cents = cents % 5;

    // The rest are pennies
    pennies = cents;

    // Print the result
    printf("That requires %d quarters, %d dimes, %d nickels, and %d pennies\n",
           quarters, dimes, nickels, pennies);

    return 0;
}