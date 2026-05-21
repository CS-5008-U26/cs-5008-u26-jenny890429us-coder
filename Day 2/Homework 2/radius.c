#include <stdio.h>
#include <math.h>

int main() {
    int radius;        // Stores the integer radius entered by the user
    double pi;         // Stores the value of pi
    double area;       // Stores the circle area as a decimal number
    int areaInt;       // Stores the integer approximation of the area

    // Get the computer's version of pi
    pi = acos(-1);

    // Ask the user to enter an integer radius
    printf("Enter an integer radius: ");
    scanf("%d", &radius);

    // Calculate the area of the circle
    area = pi * radius * radius;

    // Convert the area from double to int
    // This removes the decimal part
    areaInt = (int) area;

    // Print the result
    // %.1f prints the radius with one decimal place, like 2.0
    printf("For a circle of radius %.1f the area is %d\n", (double) radius, areaInt);

    return 0;
}