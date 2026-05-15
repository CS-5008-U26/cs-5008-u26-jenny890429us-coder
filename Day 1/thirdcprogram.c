#include <stdio.h>                  // include standard input/output library

/**** MAIN PROGRAM ****/

int main() {

    int x;                          // x will store the first number entered by the user
    int y;                          // y will store the second number entered by the user
    char s[100];                    // s is used to pause the console

    /* Ask for the first number and print it out */
    printf("Enter a number: ");     // prompt the user to enter the first number
    scanf("%d", &x);                // read the first number from the console
    fgets(s, 100, stdin);           // remove the newline left by scanf
    printf("You entered %d\n", x);  // print the first number entered by the user

    /* Ask for one more number and print it out */
    printf("Enter one more number: ");       // prompt the user to enter the second number
    scanf("%d", &y);                         // read the second number from the console
    fgets(s, 100, stdin);                    // remove the newline left by scanf
    printf("Your second number was %d\n", y); // print the second number entered by the user

    /* Pause the console so we can look at it before it vanishes */
    fgets(s, 100, stdin);           // wait for the user to press Enter before exiting

    return 0;                       // end the program successfully
}