#include <stdio.h>

/*
 * This program calculates paycheck amounts.
 * It asks the user for an hourly rate and number of hours worked.
 * If hours are over 40, the extra hours are paid at 1.5 times the hourly rate.
 * The program keeps asking for more input until either number is less than
 * or equal to 0.
 */
int main() {
    double hourlyRate;     // The amount paid per hour
    double hoursWorked;    // The number of hours worked
    double pay;            // The total amount to be paid
    double overtimeHours;  // The number of hours over 40

    while (1) {
        // Ask for the hourly rate
        printf("Enter an hourly rate: ");
        scanf("%lf", &hourlyRate); // Use %lf because hourlyRate is a double

        // Exit if the hourly rate is less than or equal to 0
        if (hourlyRate <= 0) {
            break;
        }

        // Ask for the number of hours worked
        printf("Enter the number of hours worked: ");
        scanf("%lf", &hoursWorked);

        // Exit if the number of hours is less than or equal to 0
        if (hoursWorked <= 0) {
            break;
        }

        // Calculate pay without overtime
        if (hoursWorked <= 40) {
            pay = hourlyRate * hoursWorked;
        } else {
            overtimeHours = hoursWorked - 40;
            pay = (40 * hourlyRate) + (overtimeHours * hourlyRate * 1.5);
        }

        // Print the amount due
        printf("You should be paid %.2f\n", pay);
    }

    return 0;
}