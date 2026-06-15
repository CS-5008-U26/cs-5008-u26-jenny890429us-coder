#include <stdio.h>
// For printf, fopen, fgets, and fclose.

int main(int argc, char **argv)
// argc is the number of command line arguments.
// argv stores the command line arguments.
{
    FILE *filePointer;
    // Create a file pointer.

    char inputBuffer[200];
    // Create a buffer to store one line from the file.

    if (argc <= 1)
    // If there is no file name,
    {
        return 0;
        // Do nothing.
    }

    filePointer = fopen(argv[1], "r");
    // Open the file in read mode.

    if (filePointer == NULL)
    // If the file cannot be opened,
    {
        return 0;
        // Do nothing.
    }

    while (fgets(inputBuffer, 200, filePointer) != NULL)
    // Read one line from the file until the end.
    {
        printf("%s", inputBuffer);
        // Print the line.
    }

    fclose(filePointer);
    // Close the file.

    return 0;
    // End the program.
}