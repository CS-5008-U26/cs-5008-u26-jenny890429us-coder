#include <stdio.h>
#include <ctype.h>

void condition(char *in, char *out) {
    // i is used to go through the input string.
    int i = 0;

    // j is used to keep track of the next position in the output string.
    int j = 0;

    // Go through the input string one character at a time.
    while (in[i] != '\0') {

        // Check if the current character is a letter.
        if (isalpha(in[i])) {

            // Convert the letter to lowercase and store it in the output string.
            out[j] = tolower(in[i]);

            // Move to the next position in the output string.
            j++;
        }

        // Move to the next character in the input string.
        i++;
    }

    // Add the terminating character at the end of the output string.
    out[j] = '\0';
}

int main() {
    // This buffer stores the original input from the user.
    char inputBuffer[200];

    // This buffer stores the conditioned version of the input.
    char conditionedBuffer[200];

    // Set the first character to something that is NOT '\n',
    // so the loop will run at least once.
    inputBuffer[0] = 'X';

    // Keep asking for input until the user presses ENTER only.
    while (inputBuffer[0] != '\n') {

        // Ask the user to enter a string.
        printf("Enter a string: ");

        // Read one full line from the console.
        fgets(inputBuffer, 200, stdin);

        // If the user did not just press ENTER, process the string.
        if (inputBuffer[0] != '\n') {

            // Condition the input string and store the result in conditionedBuffer.
            condition(inputBuffer, conditionedBuffer);

            // Print the conditioned string.
            printf("%s\n", conditionedBuffer);
        }
    }

    return 0;
}