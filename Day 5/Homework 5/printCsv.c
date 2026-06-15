#include <stdio.h>
// Include the standard input and output library.

#include <string.h>
// Include the string library for strlen, strchr, strcpy, and strncpy.

void killNewline(char *str)
// Define a function named killNewline. It receives a string.
{
    // Start the killNewline function.

    int len;
    // Create an integer variable to store the length of the string.

    len = strlen(str);
    // Get the length of the string. strlen does not count '\0'.

    if (len > 0 && str[len - 1] == '\n')
    // Check if the string is not empty and the last character is newline.
    {
        // Start the if statement.

        str[len - 1] = '\0';
        // Replace the newline character with the end-of-string character.

        len--;
        // Decrease len because the string is now one character shorter.
    }
    // End the if statement.

    if (len > 0 && str[len - 1] == '\r')
    // Check if the last character is carriage return, which can happen with Windows files.
    {
        // Start the if statement.

        str[len - 1] = '\0';
        // Replace the carriage return with the end-of-string character.
    }
    // End the if statement.
}
// End the killNewline function.

char *getNextField(char *start, char separator, char *out)
// Define a function to get one CSV field from a line.
{
    // Start the getNextField function.

    char *sepPointer;
    // Create a pointer to store the address of the next separator.

    int fieldLength;
    // Create an integer to store the length of the field.

    if (*start == '\0')
    // If start points to the end of the string, there are no more fields.
    {
        // Start the if statement.

        return NULL;
        // Return NULL to tell the caller to stop.
    }
    // End the if statement.

    sepPointer = strchr(start, separator);
    // Find the next separator character starting from start.

    if (sepPointer == NULL)
    // If there is no separator, this is the last field.
    {
        // Start the if statement.

        strcpy(out, start);
        // Copy the whole remaining string into out.

        return start + strlen(start);
        // Return a pointer to the end of the string.
    }
    // End the if statement.

    fieldLength = sepPointer - start;
    // Calculate how many characters are before the separator.

    strncpy(out, start, fieldLength);
    // Copy the field characters into out.

    out[fieldLength] = '\0';
    // Add '\0' to end the output string.

    return sepPointer + 1;
    // Return a pointer to the character after the separator.
}
// End the getNextField function.

int main()
// Start the main function.
{
    // Start the program.

    char filename[1000];
    // Create a buffer to store the file name from the user.

    char inputLine[1000];
    // Create a buffer to store one line from the CSV file.

    char nextField[1000];
    // Create a buffer to store one field from one CSV line.

    char s[100];
    // Create a small buffer to pause the program at the end for Windows.

    FILE *inFile;
    // Create a file pointer for the input file.

    int keepReading;
    // Create an integer used like a boolean to control the reading loop.

    char *whatWasRead;
    // Create a pointer to store the return value of fgets.

    char *p;
    // Create a pointer to move through one CSV line.

    printf("Enter the file name: ");
    // Ask the user to enter the file name.

    fgets(filename, 1000, stdin);
    // Read the file name from the keyboard.

    killNewline(filename);
    // Remove the newline character from the file name.

    inFile = fopen(filename, "r");
    // Open the file in read mode.

    if (inFile == NULL)
    // Check if the file failed to open.
    {
        // Start the if statement.

        printf("Cannot open file.\n");
        // Print an error message.

        fgets(s, 100, stdin);
        // Pause the program before it ends on Windows.

        return 1;
        // End the program with an error code.
    }
    // End the if statement.

    keepReading = 1;
    // Set keepReading to 1 so the loop starts.

    while (keepReading)
    // Keep reading while keepReading is true.
    {
        // Start the while loop.

        whatWasRead = fgets(inputLine, 1000, inFile);
        // Read one line from the file into inputLine.

        keepReading = (whatWasRead != NULL);
        // If fgets read a line, keepReading is 1. If not, keepReading is 0.

        if (keepReading)
        // If a line was successfully read, process it.
        {
            // Start the if statement.

            killNewline(inputLine);
            // Remove the newline character from the line.

            printf(">%s<\n", inputLine);
            // Print the whole CSV line between > and <.

            p = inputLine;
            // Set p to point to the beginning of the line.

            while (p != NULL)
            // Keep getting fields while p is not NULL.
            {
                // Start the field loop.

                p = getNextField(p, ',', nextField);
                // Get the next field separated by comma.

                if (p != NULL)
                // If a field was found, print it.
                {
                    // Start the if statement.

                    printf("    >%s<\n", nextField);
                    // Print the field with four spaces before it.
                }
                // End the if statement.
            }
            // End the field loop.
        }
        // End the if statement.
    }
    // End the file reading loop.

    fclose(inFile);
    // Close the file.

    fgets(s, 100, stdin);
    // Pause the program before it ends on Windows.

    return 0;
    // End the program successfully.
}
// End the main function.