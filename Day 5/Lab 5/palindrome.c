#include <stdio.h>
// For printf, fgets, fopen, and fclose.

#include <ctype.h>
// For isalpha and tolower.

void condition(char *in, char *out)
// This function keeps only letters and changes them to lowercase.
{
    int i = 0;
    // i is for the input string.

    int j = 0;
    // j is for the output string.

    while (in[i] != '\0')
    // Go through the input string.
    {
        if (isalpha(in[i]))
        // If the character is a letter,
        {
            out[j] = tolower(in[i]);
            // Put the lowercase letter into out.

            j++;
            // Move to the next position in out.
        }

        i++;
        // Move to the next character in in.
    }

    out[j] = '\0';
    // End the output string.
}

int palindrome(char *in)
// This function returns 1 if the string is a palindrome, 0 if not.
{
    char clean[200];
    // This stores the conditioned string.

    int left = 0;
    // left starts at the beginning.

    int right = 0;
    // right will find the end.

    condition(in, clean);
    // Make the clean version first.

    while (clean[right] != '\0')
    // Find the end of clean.
    {
        right++;
        // Move right forward.
    }

    right--;
    // Move right back to the last letter.

    while (left < right)
    // Compare from both sides.
    {
        if (clean[left] != clean[right])
        // If the two letters are different,
        {
            return 0;
            // It is not a palindrome.
        }

        left++;
        // Move left to the right.

        right--;
        // Move right to the left.
    }

    return 1;
    // It is a palindrome.
}

int main(int argc, char **argv)
// Main function can receive command line arguments.
{
    char inputBuffer[200];
    // This stores one line.

    FILE *filePointer;
    // This is used to read a file.

    if (argc < 2)
    // If there is no file name, read from the keyboard.
    {
        inputBuffer[0] = 'X';
        // Make sure the loop starts.

        while (inputBuffer[0] != '\n')
        // Keep asking until the user only presses ENTER.
        {
            printf("Enter a string: ");
            // Ask the user to enter a string.

            fgets(inputBuffer, 200, stdin);
            // Read one line from the keyboard.

            if (inputBuffer[0] != '\n')
            // If it is not a blank line,
            {
                if (palindrome(inputBuffer))
                // If it is a palindrome,
                {
                    printf("%s", inputBuffer);
                    // Print the original line.
                }
            }
        }
    }
    else
    // If there is a file name, read from the file.
    {
        filePointer = fopen(argv[1], "r");
        // Open the file.

        if (filePointer == NULL)
        // If the file cannot be opened,
        {
            return 0;
            // End the program.
        }

        while (fgets(inputBuffer, 200, filePointer) != NULL)
        // Read one line from the file.
        {
            if (palindrome(inputBuffer))
            // If this line is a palindrome,
            {
                printf("%s", inputBuffer);
                // Print this line.
            }
        }

        fclose(filePointer);
        // Close the file.
    }

    return 0;
    // End the program.
}