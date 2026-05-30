#include <stdio.h>

// isHarshad
// Checks whether a number is a Harshad number.
// A Harshad number is divisible by the sum of its digits.
//
// Parameters:
//     int x    the number being checked
// Returns:
//     int      1 if x is a Harshad number, 0 if it is not
int isHarshad(int x) {

    // Since this task only checks 2-digit numbers,
    // the tens digit is x / 10 and the ones digit is x % 10.
    int tens = x / 10;
    int ones = x % 10;

    // Sum of the digits.
    int digitSum = tens + ones;

    // If x is divisible by digitSum, then x is a Harshad number.
    if (x % digitSum == 0) {
        return 1;
    } else {
        return 0;
    }
}

int main() {

    // Print all 2-digit Harshad numbers.
    for (int number = 10; number <= 99; number++) {
        if (isHarshad(number)) {
            printf("%d\n", number);
        }
    }

    return 0;
}