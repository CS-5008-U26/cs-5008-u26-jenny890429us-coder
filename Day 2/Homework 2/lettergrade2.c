#include <stdio.h>

int main() {
    int score;      // Stores the number score entered by the user
    char grade;     // Stores the letter grade, such as A, B, C, D, or F

    // Ask the user to enter a number score
    printf("Enter the number score: ");
    scanf("%d", &score);

    // Check if the score is invalid
    // If the score is less than 0 or greater than 100, print an error message and stop the program
    if (score < 0 || score > 100) {
        printf("Invalid score\n");
        return 0;
    }

    // Determine the letter grade based on the score range
    if (score <= 60) {
        grade = 'F';
    } else if (score <= 70) {
        grade = 'D';
    } else if (score <= 80) {
        grade = 'C';
    } else if (score <= 90) {
        grade = 'B';
    } else {
        grade = 'A';
    }

    // Print the letter grade first
    // There is no newline here, so + or - can be printed right after the letter grade
    printf("Your grade is %c", grade);

    // Only scores from 61 to 100 need a + or - sign
    // F grades do not get a + or - sign
    if (score >= 61 && score <= 100) {
        int lastDigit = score % 10;   // Get the last digit of the score

        // If the last digit is 1, 2, or 3, print -
        if (lastDigit == 1 || lastDigit == 2 || lastDigit == 3) {
            printf("-");
        }

        // If the last digit is 8, 9, or 0, print +
        else if (lastDigit == 8 || lastDigit == 9 || lastDigit == 0) {
            printf("+");
        }

        // If the last digit is 4, 5, 6, or 7, print nothing
    }

    // Print a newline at the end
    printf("\n");

    return 0;
}