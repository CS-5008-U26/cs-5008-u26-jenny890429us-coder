#include <stdio.h>                  // include standard input/output library

/**** MAIN PROGRAM ****/

int main() {

    char name[100];                 // name will store the user's name
    char color[100];                // color will store the user's favorite color
    char s[100];                    // s is used to pause the console

    /* Ask for the user's name */
    printf("What is your name?  "); // prompt the user to enter their name
    scanf("%s", name);              // read the user's name

    /* Print the first output */
    printf("\n%s?  That's a funny name\n", name); // print a funny response using the name

    /* Ask for one more input */
    printf("What is your favorite color?  ");     // prompt the user to enter one more input
    scanf("%s", color);                           // read the user's favorite color

    /* Print one more output */
    printf("%s is a nice color\n", color);        // print one more output using the color

    /* Remove the leftover newline from scanf */
    fgets(s, 100, stdin);           // remove the leftover Enter key from scanf

    /* Pause the console so we can look at it before it vanishes */
    fgets(s, 100, stdin);           // wait for the user to press Enter before exiting

    return 0;                       // end the program successfully
}