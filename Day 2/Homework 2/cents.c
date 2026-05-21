#include <stdio.h>

int main() {
    int cents;          // Stores the number of cents entered by the user
    int quarters;       // Stores the number of quarters
    int dimes;          // Stores the number of dimes
    int nickels;        // Stores the number of nickels
    int pennies;        // Stores the number of pennies

    int coinTypes = 0;  // Counts how many types of coins are needed
    int printed = 0;    // Counts how many coin types have already been printed

    // Ask the user to enter a number of cents
    printf("Enter a number of cents: ");
    scanf("%d", &cents);

    // Check if the input is valid
    if (cents < 1 || cents > 100) {
        printf("Invalid number of cents\n");
        return 0;
    }

    // Calculate the number of quarters
    // A quarter is worth 25 cents
    quarters = cents / 25;
    cents = cents % 25;

    // Calculate the number of dimes
    // A dime is worth 10 cents
    dimes = cents / 10;
    cents = cents % 10;

    // Calculate the number of nickels
    // A nickel is worth 5 cents
    nickels = cents / 5;
    cents = cents % 5;

    // Whatever is left is pennies
    // A penny is worth 1 cent
    pennies = cents;

    // Count how many coin types are needed
    // This helps us know where to put commas and "and"
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

    // Print quarters if needed
    if (quarters > 0) {
        printf("%d ", quarters);

        if (quarters == 1) {
            printf("quarter");
        } else {
            printf("quarters");
        }

        printed++;
    }

    // Print dimes if needed
    if (dimes > 0) {
        // Print punctuation before this coin type
        if (printed > 0) {
            if (printed == coinTypes - 1) {
                if (coinTypes == 2) {
                    printf(" and ");
                } else {
                    printf(", and ");
                }
            } else {
                printf(", ");
            }
        }

        printf("%d ", dimes);

        if (dimes == 1) {
            printf("dime");
        } else {
            printf("dimes");
        }

        printed++;
    }

    // Print nickels if needed
    if (nickels > 0) {
        // Print punctuation before this coin type
        if (printed > 0) {
            if (printed == coinTypes - 1) {
                if (coinTypes == 2) {
                    printf(" and ");
                } else {
                    printf(", and ");
                }
            } else {
                printf(", ");
            }
        }

        printf("%d ", nickels);

        if (nickels == 1) {
            printf("nickel");
        } else {
            printf("nickels");
        }

        printed++;
    }

    // Print pennies if needed
    if (pennies > 0) {
        // Print punctuation before this coin type
        if (printed > 0) {
            if (printed == coinTypes - 1) {
                if (coinTypes == 2) {
                    printf(" and ");
                } else {
                    printf(", and ");
                }
            } else {
                printf(", ");
            }
        }

        printf("%d ", pennies);

        if (pennies == 1) {
            printf("penny");
        } else {
            printf("pennies");
        }

        printed++;
    }

    // Print period and newline at the end
    printf(".\n");

    return 0;
}