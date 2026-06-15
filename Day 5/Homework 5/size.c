#include <stdio.h>      // for printf, fgets
#include <string.h>     // for strlen, strcpy
#include <sys/stat.h>   // for struct stat and stat

int main(int argc, char **argv) {
    char filename[200];          // stores the file name
    char s[100];                 // used to pause at the end for Windows
    struct stat fileStat;        // stores information about the file

    // If the user gave a command-line argument,
    // use argv[1] as the file name.
    if (argc > 1) {
        strcpy(filename, argv[1]);
    }

    // If no command-line argument was given,
    // ask the user to type a file name.
    else {
        printf("Enter the name of a file: ");
        fgets(filename, 200, stdin);

        // fgets keeps the newline character '\n',
        // so we remove it before using the filename.
        if (filename[strlen(filename) - 1] == '\n') {
            filename[strlen(filename) - 1] = '\0';
        }
    }

    // stat gets information about the file.
    // If stat returns 0, it worked.
    // If stat returns a negative number, it failed.
    if (stat(filename, &fileStat) < 0) {
        printf("Could not get information about %s\n", filename);

        // Pause before closing on Windows.
        fgets(s, 100, stdin);

        return 1;
    }

    // st_size is the size of the file in bytes.
    printf("%s has %lld bytes\n", filename, (long long)fileStat.st_size);

    // Pause before closing on Windows.
    fgets(s, 100, stdin);

    return 0;
}