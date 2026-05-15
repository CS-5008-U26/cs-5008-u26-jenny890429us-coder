/* secondcprogram.c */                                      

/* This program asks the user for their name. */             
/* Then it prints a funny response using that name. */       

/* Changes made: */                                         
/* 1. Added proper comments to explain the program. */       
/* 2. Changed printf to print s instead of t. */             
/* 3. Moved fgets after printf so the message prints first. */
/* 4. Added a second fgets so the window waits for Enter. */ 
      

#include <stdio.h>                                          // Include standard input and output library

int main() {                                                // Start the main function

    char s[100];                                            // Store the user's name
    char t[100];                                            // Used to pause the console window

    printf("What is your name?  ");                         // Ask the user for their name

    scanf("%s", s);                                         // Read the user's name and store it in s

    printf("\n%s?  That's a funny name\n", s);              // Print the name and funny message

    fgets(t, 100, stdin);                                   // Read the leftover Enter key from scanf

    fgets(t, 100, stdin);                                   // Wait for the user to press Enter before closing

    return 0;                                               // End the program successfully

}                                                           // End the main function