#include <stdio.h>

int main() {
    int number;   // The integer entered by the user

    // Ask the user to enter a number between 1 and 4000
    printf("Enter a number between 1 and 4000: ");
    scanf("%d", &number);

    // Check whether the number is outside the allowed range
    if (number < 1 || number > 4000) {
        printf("Error: The number must be between 1 and 4000.\n");
        return 0;
    }

    // Start printing the Roman numeral
    printf("The Roman Numeral: ");

    /*
     * Roman numerals are built from largest value to smallest value.
     * After printing each Roman symbol, subtract its value from number.
     */

    // Print M for each 1000
    while (number >= 1000) {
        printf("M");
        number = number - 1000;
    }

    /*
     * Handle hundreds.
     * 900 is CM because it means 100 before 1000.
     * 400 is CD because it means 100 before 500.
     */

    // Print CM for 900
    if (number >= 900) {
        printf("CM");
        number = number - 900;
    }

    // Print D for 500
    if (number >= 500) {
        printf("D");
        number = number - 500;
    }

    // Print CD for 400
    if (number >= 400) {
        printf("CD");
        number = number - 400;
    }

    // Print C for each 100
    while (number >= 100) {
        printf("C");
        number = number - 100;
    }

    /*
     * Handle tens.
     * 90 is XC because it means 10 before 100.
     * 40 is XL because it means 10 before 50.
     */

    // Print XC for 90
    if (number >= 90) {
        printf("XC");
        number = number - 90;
    }

    // Print L for 50
    if (number >= 50) {
        printf("L");
        number = number - 50;
    }

    // Print XL for 40
    if (number >= 40) {
        printf("XL");
        number = number - 40;
    }

    // Print X for each 10
    while (number >= 10) {
        printf("X");
        number = number - 10;
    }

    /*
     * Handle ones.
     * 9 is IX because it means 1 before 10.
     * 4 is IV because it means 1 before 5.
     */

    // Print IX for 9
    if (number >= 9) {
        printf("IX");
        number = number - 9;
    }

    // Print V for 5
    if (number >= 5) {
        printf("V");
        number = number - 5;
    }

    // Print IV for 4
    if (number >= 4) {
        printf("IV");
        number = number - 4;
    }

    // Print I for each 1
    while (number >= 1) {
        printf("I");
        number = number - 1;
    }

    // Move to a new line after the Roman numeral is printed
    printf("\n");

    return 0;
}