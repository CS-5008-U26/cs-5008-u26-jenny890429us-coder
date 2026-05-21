#include <stdio.h>

/*
 * This program prints all numbers from 0 to 1500
 * that are multiples of 63.
 * Each number is printed right-justified in a column.
 */
int main() {
    int n;  // The current number to print

    // Start at 0 and add 63 each time until n is greater than 1500
    for (n = 0; n <= 1500; n = n + 63) {
        printf("%6d\n", n);  // Print n right-justified in a field of width 6
    }

    return 0;
}