#include <stdio.h>

/**** MAIN PROGRAM ****/

int main() {

    int x;                          // first number entered by the user
    int y;                          // second number entered by the user
    char s[100];                    // s is used to "pause" the console

    /* Ask for a number and print it out */
    printf("Enter a number: ");
    scanf("%d", &x);
    fgets(s, 100, stdin);
    printf("You entered %d\n", x);

    /* Ask for one more number and print it out */
    printf("Enter one more number: ");
    scanf("%d", &y);
    fgets(s, 100, stdin);
    printf("Your second number was %d\n", y);

    /* Pause the console so we can look at it before it vanishes */
    fgets(s, 100, stdin);

    return 0;
}