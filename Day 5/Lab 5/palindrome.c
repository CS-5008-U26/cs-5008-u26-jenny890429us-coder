#include <stdio.h>   

int main() {
    // Create a character array to store the user's input.
    // The assignment says 200 characters is enough.
    char inputBuffer[200];

    // Set the first character to something that is NOT '\n',
    // so the while loop will run at least once.
    inputBuffer[0] = 'X';

    // Keep looping until the user only presses ENTER.
    // If the user only presses ENTER, inputBuffer[0] will be '\n'.
    while (inputBuffer[0] != '\n') {

        // Ask the user to enter a string.
        printf("Enter a string: ");

        // Read one full line from the console.
        // inputBuffer is where the string will be stored.
        // 200 is the maximum size of the buffer.
        // stdin means standard input, which is the keyboard.
        fgets(inputBuffer, 200, stdin);

        // If the user did NOT just press ENTER,
        // print the string back to the console.
        if (inputBuffer[0] != '\n') {
            printf("%s", inputBuffer);
        }
    }

    return 0;
}