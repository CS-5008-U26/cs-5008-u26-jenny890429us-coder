#include <stdio.h>
#include <string.h>

int main() {
    // Create a character buffer to store the user's input.
    // The buffer can hold up to 199 characters plus the null character '\0'.
    char inputBuffer[200];

    // Set the first character to something that is NOT '\n',
    // so the while loop will run at least once.
    inputBuffer[0] = 'X';

    // Keep asking the user for input until they press ENTER only.
    while (inputBuffer[0] != '\n') {

        // Ask the user to enter a string.
        printf("Enter a string: ");

        // Read one full line from the console and store it in inputBuffer.
        fgets(inputBuffer, 200, stdin);

        // If the user did not just press ENTER,
        // print the string and its length.
        if (inputBuffer[0] != '\n') {

            // Print the string that the user entered.
            printf("%s", inputBuffer);

            // strlen(inputBuffer) counts all characters, including '\n'.
            // Since the assignment says NOT to count the newline,
            // we subtract 1 from the length.
            printf("%d\n", (int)(strlen(inputBuffer) - 1));
        }
    }

    return 0;
}