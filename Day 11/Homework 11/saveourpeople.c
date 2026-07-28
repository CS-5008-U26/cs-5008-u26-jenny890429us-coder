/* saveourpeople.c - Aliens Attack!
 *
 * Read the 200 largest cities from uscities.csv.
 * Use dynamic programming to find the group of cities
 * with the largest total population whose names use
 * no more than 200 characters.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/***   D A T A   ***/

#define N_CITIES 200
#define MAX_CHARACTERS 200
#define LINE_SIZE 10000

// Information needed for each city
typedef struct cityStruct {
    char *name;
    int nameLength;
    long long population;
} city;

/*
 * table[i][characters] stores the largest population
 * that can be saved using the first i cities and no
 * more than characters characters.
 */
long long table[N_CITIES + 1][MAX_CHARACTERS + 1];


/***   R E A D   T H E   C I T Y   F I L E   ***/

// Remove quotation marks and newline characters
void removeQuotes(char *field) {
    int length;

    if (field == NULL) {
        return;
    }

    // Remove newline characters
    field[strcspn(field, "\r\n")] = '\0';

    length = strlen(field);

    // Remove the quotation mark at the beginning
    if (length > 0 && field[0] == '"') {
        memmove(field, field + 1, length);
    }

    length = strlen(field);

    // Remove the quotation mark at the end
    if (length > 0 && field[length - 1] == '"') {
        field[length - 1] = '\0';
    }
}


// Get the next field from one CSV line
char *getNextField(char *line) {
    char *field;

    field = strtok(line, ",");

    if (field == NULL) {
        printf("Error: missing field in CSV line.\n");
        exit(1);
    }

    removeQuotes(field);

    return field;
}


// Convert one CSV line into one city struct
city *stringToCity(char *textLine) {
    city *c;
    char *field;
    int column;

    c = malloc(sizeof(city));

    if (c == NULL) {
        printf("Could not allocate memory for city.\n");
        exit(1);
    }

    // Column 1: city name
    field = getNextField(textLine);
    c->name = strdup(field);

    if (c->name == NULL) {
        printf("Could not allocate memory for city name.\n");
        free(c);
        exit(1);
    }

    // The number of characters used by this city name
    c->nameLength = strlen(c->name);

    /*
     * Skip columns 2 through 8:
     * city_ascii, state_id, state_name, county_fips,
     * county_name, latitude, and longitude.
     */
    for (column = 2; column <= 8; column++) {
        getNextField(NULL);
    }

    // Column 9: population
    field = getNextField(NULL);
    c->population = atoll(field);

    return c;
}


// Read the first 200 cities from the CSV file
city **readCityList(char *filename) {
    FILE *file;
    city **cityList;
    char line[LINE_SIZE];
    int i;

    file = fopen(filename, "r");

    if (file == NULL) {
        printf("Could not open file: %s\n", filename);
        exit(1);
    }

    // Create an array for 200 city pointers
    cityList = malloc(N_CITIES * sizeof(city *));

    if (cityList == NULL) {
        printf("Could not allocate memory for city list.\n");
        fclose(file);
        exit(1);
    }

    // Read and ignore the CSV header
    if (fgets(line, LINE_SIZE, file) == NULL) {
        printf("Could not read the header line.\n");
        free(cityList);
        fclose(file);
        exit(1);
    }

    // Read the first 200 cities
    for (i = 0; i < N_CITIES; i++) {
        if (fgets(line, LINE_SIZE, file) == NULL) {
            printf("Could not read city line %d.\n", i + 1);
            fclose(file);
            exit(1);
        }

        cityList[i] = stringToCity(line);
    }

    fclose(file);

    return cityList;
}


/***   D Y N A M I C   P R O G R A M M I N G   ***/

// Fill the dynamic programming table
void findMaximumPopulation(city **cityList) {
    city *currentCity;
    long long withoutCity;
    long long withCity;
    int i;
    int characters;

    /*
     * If we have zero cities, the saved population
     * is zero for every possible character limit.
     */
    for (characters = 0;
         characters <= MAX_CHARACTERS;
         characters++) {

        table[0][characters] = 0;
    }

    /*
     * Consider each city one at a time.
     */
    for (i = 1; i <= N_CITIES; i++) {
        currentCity = cityList[i - 1];

        for (characters = 0;
             characters <= MAX_CHARACTERS;
             characters++) {

            /*
             * Option 1:
             * Do not save the current city.
             */
            withoutCity = table[i - 1][characters];
            table[i][characters] = withoutCity;

            /*
             * Option 2:
             * Save the current city if its name fits.
             */
            if (currentCity->nameLength <= characters) {
                withCity =
                    currentCity->population +
                    table[i - 1]
                         [characters - currentCity->nameLength];

                /*
                 * Keep the option that saves more people.
                 */
                if (withCity > withoutCity) {
                    table[i][characters] = withCity;
                }
            }
        }
    }
}


// Trace backward through the table and print the cities
void printSavedCities(city **cityList) {
    int selected[N_CITIES] = {0};
    int charactersRemaining;
    int totalCharacters;
    int numberOfCities;
    int i;

    charactersRemaining = MAX_CHARACTERS;
    totalCharacters = 0;
    numberOfCities = 0;

    /*
     * Start at the bottom-right corner of the table.
     *
     * If the value changed when city i was added,
     * then that city is part of the best solution.
     */
    for (i = N_CITIES; i > 0; i--) {
        if (table[i][charactersRemaining] !=
            table[i - 1][charactersRemaining]) {

            selected[i - 1] = 1;

            charactersRemaining -=
                cityList[i - 1]->nameLength;
        }
    }

    printf(
        "Maximum population saved: %lld\n\n",
        table[N_CITIES][MAX_CHARACTERS]
    );

    printf("Cities saved:\n");

    // Print selected cities in their original order
    for (i = 0; i < N_CITIES; i++) {
        if (selected[i] == 1) {
            printf("%s\n", cityList[i]->name);

            totalCharacters += cityList[i]->nameLength;
            numberOfCities++;
        }
    }

    /*
     * These last two lines help verify that the
     * solution stays within the 200-character limit.
     */
    printf(
        "\nNumber of cities saved: %d\n",
        numberOfCities
    );

    printf(
        "Total city-name characters: %d\n",
        totalCharacters
    );
}


/***   F R E E   M E M O R Y   ***/

// Free one city
void freeCity(city *c) {
    if (c == NULL) {
        return;
    }

    free(c->name);
    free(c);
}


// Free the entire city list
void freeCityList(city **cityList) {
    int i;

    for (i = 0; i < N_CITIES; i++) {
        freeCity(cityList[i]);
    }

    free(cityList);
}


/***   M A I N   ***/

int main(void) {
    city **cityList;

    // Read the 200 largest cities
    cityList = readCityList("uscities.csv");

    // Find the best set of cities
    findMaximumPopulation(cityList);

    // Print the answer
    printSavedCities(cityList);

    // Free dynamically allocated memory
    freeCityList(cityList);

    return 0;
}