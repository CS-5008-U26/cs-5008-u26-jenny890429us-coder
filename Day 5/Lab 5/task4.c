#include <stdio.h>
#include <string.h>
#include <ctype.h>

// This function removes non-letter characters
// and converts all letters to lowercase.
void condition(char *in, char *out) {
    int i = 0;
    int j = 0;

    // Go through each character in the input string.
    while (in[i] != '\0') {

        // If the character is a letter, keep it.
        if (isalpha(in[i])) {

            // Convert the letter to lowercase and put it in the output string.
            out[j] = tolower(in[i]);

            // Move to the next position in the output string.
            j++;
        }

        // Move to the next character in the input string.
        i++;
    }

    // Add the string ending character.
    out[j] = '\0';
}

// This function returns 1 if the string is a palindrome,
// and returns 0 if it is not.
int palindrome(char *in) {
    // Create a buffer to hold the conditioned string.
    char conditionedBuffer[200];

    // Condition the input string first.
    condition(in, conditionedBuffer);

    // Find the length of the conditioned string.
    int length = strlen(conditionedBuffer);

    // left starts at the beginning.
    int left = 0;

    // right starts at the last character.
    int right = length - 1;

    // Compare characters from both ends.
    while (left < right) {

        // If the characters do not match,
        // the string is not a palindrome.
        if (conditionedBuffer[left] != conditionedBuffer[right]) {
            return 0;
        }

        // Move left forward and right backward.
        left++;
        right--;
    }

    // If all matching characters are the same,
    // the string is a palindrome.
    return 1;
}

int main() {
    // This buffer stores the user's original input.
    char inputBuffer[200];

    // Set the first character to something that is NOT '\n',
    // so the loop will run at least once.
    inputBuffer[0] = 'X';

    // Keep asking for strings until the user presses ENTER only.
    while (inputBuffer[0] != '\n') {

        // Ask the user to enter a string.
        printf("Enter a string: ");

        // Read one full line from the console.
        fgets(inputBuffer, 200, stdin);

        // If the user did not just press ENTER,
        // check if the string is a palindrome.
        if (inputBuffer[0] != '\n') {

            // If the input string is a palindrome, print the original string.
            if (palindrome(inputBuffer)) {
                printf("%s", inputBuffer);
            }
        }
    }

    return 0;
}