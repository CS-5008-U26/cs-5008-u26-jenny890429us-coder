#include <stdio.h>

/*
 * This program asks the user for a number score from 1 to 10.
 * It prints the matching letter grade using switch.
 * If the score is outside the range 1 to 10, it prints an error message.
 */
int main() {
    int number;   // The number score entered by the user
    char grade;   // The letter grade
    
    // Ask the user to enter a number score
    printf("Enter the number score: ");
    scanf("%d", &number);

    /*
     * Use switch to match the number score.
     * Some grades have more than one matching number.
     * For example, both 9 and 10 should receive an A.
     */

    switch (number) {
        // Scores 9 and 10 receive an A
        case 9:
        case 10:
            grade = 'A';
            printf("Your grade is %c\n", grade);
            break;
        
        // Score 8 receives a B
        case 8:
            grade = 'B';
            printf("Your grade is %c\n", grade);
            break;
        
        // Score 7 receives a C    
        case 7:
            grade = 'C';
            printf("Your grade is %c\n", grade);
            break;

        // Score 6 receives a D
        case 6:
            grade = 'D';
            printf("Your grade is %c\n", grade);
            break;

        // Scores 4 and 5 receive an E    
        case 4:
        case 5:
            grade = 'E';
            printf("Your grade is %c\n", grade);
            break;


        // Scores 1, 2, and 3 receive an F
        case 1:
        case 2:
        case 3:
            grade = 'F';
            printf("Your grade is %c\n", grade);
            break;
        
        /*
         * The default case runs when none of the above cases match.
         * That means the number is less than 1 or greater than 10.
         */
        default:
            printf("Error: the score must be between 1 and 10.\n");
            break;
    }

    return 0;
}