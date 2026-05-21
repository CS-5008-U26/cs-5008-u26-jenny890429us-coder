#include <stdio.h>

/*
 * This program asks the user for a number score from 1 to 10.
 * It prints the matching letter grade using if and else.
 * If the score is outside the range 1 to 10, it prints an error message.
 */
int main() {
    int number;   // The number score entered by the user
    char grade;   // The letter grade
    
    // Ask the user to enter a number score
    printf("Enter the number score: ");
    scanf("%d", &number);
    
    // Check whether the number is outside the valid range
    if (number < 1 || number > 10) {
        printf("Error: the score must be between 1 and 10.\n");
    } 
    
    // Scores 9 and 10 receive an A
    else if (number >= 9) {
        grade = 'A';
        printf("Your grade is %c\n", grade);
    } 
    
    // Scores 8 receive a B
    else if (number == 8) {
        grade = 'B';
        printf("Your grade is %c\n", grade);
    } 

    // Scores 7 receive a C
    else if (number == 7) {
        grade = 'C';
        printf("Your grade is %c\n", grade);
    } 

    // Scores 6 receive a D
    else if (number == 6) {
        grade = 'D';
        printf("Your grade is %c\n", grade);
    } 

    // Scores 4-5 receive an E
    else if (number >= 4) {
        grade = 'E';
        printf("Your grade is %c\n", grade);
    } 
    
    // Scores 1-3 receive an F
    else {
        grade = 'F';
        printf("Your grade is %c\n", grade);
    }

    return 0;
}