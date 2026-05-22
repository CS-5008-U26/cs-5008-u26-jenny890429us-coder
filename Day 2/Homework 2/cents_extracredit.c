#include <stdio.h>

int main() {
    int cents;       // Total number of cents entered by the user
    int quarters;    // Number of quarters needed
    int dimes;       // Number of dimes needed
    int nickels;     // Number of nickels needed
    int pennies;     // Number of pennies needed

    int coinTypes;   // Number of coin types that are greater than 0
    int printed;     // Number of coin types already printed

    // Ask the user for the number of cents
    printf("Enter a number of cents: ");
    scanf("%d", &cents);

    // Find the number of quarters
    quarters = cents / 25;

    // Keep only the cents left after using quarters
    cents = cents % 25;

    // Find the number of dimes
    dimes = cents / 10;

    // Keep only the cents left after using dimes
    cents = cents % 10;

    // Find the number of nickels
    nickels = cents / 5;

    // Keep only the cents left after using nickels
    cents = cents % 5;

    // The remaining cents are pennies
    pennies = cents;

    // Count how many different coin types are needed
    coinTypes = 0;

    if (quarters > 0) {
        coinTypes++;
    }

    if (dimes > 0) {
        coinTypes++;
    }

    if (nickels > 0) {
        coinTypes++;
    }

    if (pennies > 0) {
        coinTypes++;
    }

    // Start printing the result
    printf("That requires ");

    // Nothing has been printed yet
    printed = 0;

    // Print quarters only if they are needed
    if (quarters > 0) {
        if (quarters == 1) {
            printf("%d quarter", quarters);
        } else {
            printf("%d quarters", quarters);
        }

        printed++;
    }

    // Print dimes only if they are needed
    if (dimes > 0) {

        // Print a comma or "and" before this coin if needed
        if (printed > 0) {
            if (printed == coinTypes - 1) {
                printf(", and ");
            } else {
                printf(", ");
            }
        }

        if (dimes == 1) {
            printf("%d dime", dimes);
        } else {
            printf("%d dimes", dimes);
        }

        printed++;
    }

    // Print nickels only if they are needed
    if (nickels > 0) {

        // Print a comma or "and" before this coin if needed
        if (printed > 0) {
            if (printed == coinTypes - 1) {
                printf(", and ");
            } else {
                printf(", ");
            }
        }

        if (nickels == 1) {
            printf("%d nickel", nickels);
        } else {
            printf("%d nickels", nickels);
        }

        printed++;
    }

    // Print pennies only if they are needed
    if (pennies > 0) {

        // Print a comma or "and" before this coin if needed
        if (printed > 0) {
            if (printed == coinTypes - 1) {
                printf(", and ");
            } else {
                printf(", ");
            }
        }

        if (pennies == 1) {
            printf("%d penny", pennies);
        } else {
            printf("%d pennies", pennies);
        }

        printed++;
    }

    // End the sentence
    printf(".\n");

    return 0;
}