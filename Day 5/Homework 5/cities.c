#include <stdio.h>      // for FILE, fopen, fgets, fclose, printf
#include <stdlib.h>     // for atoi and atof
#include <string.h>     // for strcpy

#define MAX_LINE 10000  // large enough for long CSV lines

// Get one field from a CSV line.
// fieldNumber starts at 1.
// Example: fieldNumber 2 means the second column.
void getField(char line[], int fieldNumber, char result[]) {
    int i = 0;              // index for line
    int j = 0;              // index for result
    int currentField = 1;   // current column number
    int inQuotes = 0;       // 1 means we are inside quotes

    // Move to the field we want.
    while (line[i] != '\0' && currentField < fieldNumber) {

        // If we see a quote, switch inQuotes.
        if (line[i] == '"') {
            inQuotes = !inQuotes;
        }

        // If we see a comma and we are not inside quotes,
        // then we move to the next field.
        else if (line[i] == ',' && inQuotes == 0) {
            currentField++;
        }

        // Move to next character.
        i++;
    }

    // Start copying the field.
    j = 0;
    inQuotes = 0;

    // Copy the field into result.
    while (line[i] != '\0') {

        // If we see a quote, skip it.
        if (line[i] == '"') {
            inQuotes = !inQuotes;
            i++;
        }

        // If we see a comma and we are not inside quotes,
        // this field is finished.
        else if (line[i] == ',' && inQuotes == 0) {
            break;
        }

        // If we see newline, this field is finished.
        else if (line[i] == '\n' || line[i] == '\r') {
            break;
        }

        // Otherwise copy this character.
        else {
            result[j] = line[i];
            j++;
            i++;
        }
    }

    // End the string.
    result[j] = '\0';
}

int main() {
    FILE *inFile;                 // file pointer
    char line[MAX_LINE];          // one full line from the CSV file

    char city[100];               // city name
    char latitudeString[100];     // latitude as a string
    char populationString[100];   // population as a string

    char northernCity[100];       // northernmost city name

    int count = 0;                // how many city lines we processed
    int population;               // population of one city
    long long populationSum = 0;  // total population

    double latitude;              // latitude of one city
    double northernLatitude = -1000.0; // very small starting latitude

    char s[100];                  // used to pause at the end for Windows

    // Open the CSV file.
    // Make sure uscities.csv is in the same folder as cities.c.
    inFile = fopen("uscities.csv", "r");

    // Check if the file opened successfully.
    if (inFile == NULL) {
        printf("Could not open file.\n");

        // Pause before closing on Windows.
        fgets(s, 100, stdin);

        return 1;
    }

    // Read and ignore the first line.
    // The first line is the header.
    fgets(line, MAX_LINE, inFile);

    // Read only the next 20 city lines.
    while (count < 20 && fgets(line, MAX_LINE, inFile) != NULL) {

        // Column 2 is city_ascii.
        getField(line, 2, city);

        // Column 7 is latitude.
        getField(line, 7, latitudeString);

        // Column 9 is population.
        getField(line, 9, populationString);

        // Convert population string to int.
        population = atoi(populationString);

        // Convert latitude string to double.
        latitude = atof(latitudeString);

        // Add population to total.
        populationSum = populationSum + population;

        // Larger latitude means farther north.
        if (latitude > northernLatitude) {
            northernLatitude = latitude;
            strcpy(northernCity, city);
        }

        // This line is for testing.
        // It helps check that the city, latitude, and population are correct.
        // printf("%d: %s, %s, %s\n", count + 1, city, latitudeString, populationString);

        // We processed one more city.
        count++;
    }

    // Close the file.
    fclose(inFile);

    // Print final results.
    printf("Sum of the populations: %lld\n", populationSum);
    printf("Northernmost city is %s\n", northernCity);

    // Pause before closing on Windows.
    fgets(s, 100, stdin);

    return 0;
}