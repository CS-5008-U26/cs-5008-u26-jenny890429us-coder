#include <stdio.h>
// For printf.

void main(int argc, char **argv)
// argc is the number of command line strings.
// argv is the array of command line strings.
{
    int i;
    // i is used for the loop.

    for (i = 0; i < argc; i++)
    // Loop through all command line arguments.
    {
        printf("%s\n", argv[i]);
        // Print one argument on each line.
    }
}
