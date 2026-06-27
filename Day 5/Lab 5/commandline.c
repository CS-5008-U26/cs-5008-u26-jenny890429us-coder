#include <stdio.h>


int main(int argc, char **argv)
// argc is the number of command line arguments.
// argv stores the command line arguments.
{
    FILE *filePointer;
    // File pointer used to open and read the file.

    char inputBuffer[200];
    // Buffer to store one line from the file.

    if (argc <= 1)
    // If there is no file name on the command line,
    {
        return 0;
        // Do nothing.
    }

    filePointer = fopen(argv[1], "r");
    // Open the file name from argv[1].

    if (filePointer == NULL)
    // If the file cannot be opened,
    {
        return 0;
        // Do nothing.
    }

    while (fgets(inputBuffer, 200, filePointer) != NULL)
    // Read one line at a time until the end of the file.
    {
        printf("%s", inputBuffer);
        // Print the line.
    }

    fclose(filePointer);
    // Close the file.

    return 0;
    // End the program.
}