#include <stdio.h>
// Include the standard input and output library.

#include <string.h>
// Include the string library for strlen and strncpy.

void killNewline(char *str)
// This function removes the newline character from the end of a string.
{
    int len;
    // Store the length of the string.

    len = strlen(str);
    // Get the length of the string.

    if (len > 0 && str[len - 1] == '\n')
    // If the last character is '\n',
    {
        str[len - 1] = '\0';
        // Replace '\n' with '\0'.
    }
}

void removeQuotes(char *str)
// This function removes outside double quotes from a field.
{
    int len;
    // Store the length of the string.

    int i;
    // Loop variable.

    len = strlen(str);
    // Get the length of the string.

    if (len >= 2 && str[0] == '"' && str[len - 1] == '"')
    // If the field starts and ends with double quotes,
    {
        for (i = 0; i < len - 2; i++)
        // Move the inside characters one position left.
        {
            str[i] = str[i + 1];
            // Copy the next character to the current position.
        }

        str[len - 2] = '\0';
        // End the string before the last quote.
    }
}

char *getNextField(char *start, char separator, char *out)
// This function gets one field from a CSV line.
{
    char *p;
    // p moves through the line.

    int i;
    // i is used to copy characters.

    int inQuotes;
    // inQuotes tells us if we are inside double quotes.

    if (*start == '\0')
    // If start is already at the end of the string,
    {
        return NULL;
        // There are no more fields.
    }

    p = start;
    // Start p at the beginning of the field.

    inQuotes = 0;
    // At the beginning, we are not inside quotes.

    while (*p != '\0')
    // Keep going until the end of the line.
    {
        if (*p == '"')
        // If we see a double quote,
        {
            inQuotes = !inQuotes;
            // Change inQuotes from 0 to 1, or from 1 to 0.
        }
        else if (*p == separator && inQuotes == 0)
        // If we see a comma and we are not inside quotes,
        {
            break;
            // This field is finished.
        }

        p++;
        // Move to the next character.
    }

    for (i = 0; start + i < p; i++)
    // Copy the field into out.
    {
        out[i] = start[i];
        // Copy one character.
    }

    out[i] = '\0';
    // Add the end-of-string character.

    removeQuotes(out);
    // Remove outside quotes if there are any.

    if (*p == separator)
    // If p stopped at a comma,
    {
        return p + 1;
        // Return the next character after the comma.
    }

    return p;
    // Otherwise return the end of the string.
}

int main()
// Start the main function.
{
    char filename[1000];
    // Store the file name.

    char inputLine[1000];
    // Store one line from the file.

    char nextField[1000];
    // Store one field from the line.

    char *p;
    // Pointer used to move through the line.

    FILE *inFile;
    // File pointer.

    char s[100];
    // Used to pause the program at the end for Windows.

    printf("Enter the file name: ");
    // Ask the user to enter the file name.

    fgets(filename, 1000, stdin);
    // Read the file name.

    killNewline(filename);
    // Remove the newline from the file name.

    inFile = fopen(filename, "r");
    // Open the file for reading.

    if (inFile == NULL)
    // If the file could not be opened,
    {
        printf("Cannot open file.\n");
        // Print an error message.

        fgets(s, 100, stdin);
        // Pause before closing on Windows.

        return 1;
        // End the program with an error.
    }

    while (fgets(inputLine, 1000, inFile) != NULL)
    // Read the file one line at a time.
    {
        killNewline(inputLine);
        // Remove the newline from the line.

        printf(">%s<\n", inputLine);
        // Print the whole line.

        p = inputLine;
        // Start at the beginning of the line.

        while (p != NULL)
        // Keep getting fields until there are no more fields.
        {
            p = getNextField(p, ',', nextField);
            // Get the next field.

            if (p != NULL)
            // If a field was found,
            {
                printf("    >%s<\n", nextField);
                // Print the field.
            }
        }
    }

    fclose(inFile);
    // Close the file.

    fgets(s, 100, stdin);
    // Pause before closing on Windows.

    return 0;
    // End the program successfully.
}