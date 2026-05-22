#include <stdio.h>

int main() {
    double price;          // Price entered by the user
    double priceWithTax;   // Price after adding tax

    // Keep asking for prices until the user enters 0
    while (1) {
        printf("Enter a price in dollars: ");
        scanf("%lf", &price);

        // Exit the loop if the user enters 0
        if (price == 0) {
            break;
        }

        // Add 8% tax
        priceWithTax = price * 1.08;

        // Print the result with two decimal places
        printf("The value with tax is $%.2f\n", priceWithTax);
    }

    return 0;
}