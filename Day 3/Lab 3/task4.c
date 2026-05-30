#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// count
// Generates p random numbers in the range from 0 to q.
// Returns how many of them are in the range from 0 to r.
//
// Valid parameters:
//     p must be greater than 0
//     q must be greater than or equal to 0
//     r must be greater than or equal to 0
//     r must be less than or equal to q
//
// Parameters:
//     int p    how many random numbers to generate
//     int q    the maximum random value
//     int r    the upper limit of the range being counted
// Returns:
//     int      how many random numbers are between 0 and r
//              -1 if any parameter is invalid
int count(int p, int q, int r) {

    // Check whether the parameters are valid.
    if (p <= 0) {
        return -1;
    }

    if (q < 0) {
        return -1;
    }

    if (r < 0) {
        return -1;
    }

    if (r > q) {
        return -1;
    }

    // result stores how many random numbers are between 0 and r.
    int result = 0;

    // Generate p random numbers.
    for (int i = 0; i < p; i++) {

        // rand() % (q + 1) gives a number from 0 to q.
        int randomNumber = rand() % (q + 1);

        // Count it if it is in the range from 0 to r.
        if (randomNumber <= r) {
            result++;
        }
    }

    return result;
}

int main() {

    char s[100];

    int p;
    int q;
    int r;

    // Seed the random number generator once at the start of the program.
    srand(time(NULL));

    // First, test invalid parameters.
    printf("Testing invalid parameters:\n");
    printf("count(-1, 10, 5) = %d\n", count(-1, 10, 5));
    printf("count(10, -1, 5) = %d\n", count(10, -1, 5));
    printf("count(10, 10, -1) = %d\n", count(10, 10, -1));
    printf("count(10, 5, 10) = %d\n", count(10, 5, 10));

    // Loop to get values from the user.
    while (1) {

        printf("\nEnter p, q, and r: ");
        scanf("%d %d %d", &p, &q, &r);
        fgets(s, 100, stdin);

        // If the user enters 0 for p, exit the program.
        if (p == 0) {
            printf("Goodbye.\n");
            break;
        }

        // Check validity before calling count.
        if (p <= 0 || q < 0 || r < 0 || r > q) {
            printf("Invalid parameters.\n");
        } else {
            int result = count(p, q, r);
            printf("The count is %d\n", result);
        }
    }

    fgets(s, 100, stdin);

    return 0;
}