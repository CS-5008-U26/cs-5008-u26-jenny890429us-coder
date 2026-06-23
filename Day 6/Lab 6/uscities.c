#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
    Task 1A

    Define a struct named city.
    The first 6 fields are strings.
    lat and lng are doubles.
    population is an int.
*/
typedef struct city {
    char *name;
    char *city_ascii;
    char *state_id;
    char *state_name;
    char *county_fips;
    char *county_name;
    double lat;
    double lng;
    int population;
} city;


/*
    This function removes quotation marks and newline characters.

    Example:
    "New York" becomes New York
*/
void removeQuotes(char *field) {
    int len;

    if (field == NULL) {
        return;
    }

    /* Remove newline characters */
    field[strcspn(field, "\r\n")] = '\0';

    len = strlen(field);

    /* Remove the first quotation mark */
    if (len > 0 && field[0] == '"') {
        memmove(field, field + 1, len);
    }

    len = strlen(field);

    /* Remove the last quotation mark */
    if (len > 0 && field[len - 1] == '"') {
        field[len - 1] = '\0';
    }
}


/*
    This function gets the next field from a CSV line.

    First call:
        getNextField(textLine)

    Later calls:
        getNextField(NULL)
*/
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


/*
    Task 1B

    Convert one line of text from the CSV file
    into one city struct.
*/
city *stringToCity(char *textLine) {
    city *c;
    char *field;

    c = malloc(sizeof(city));

    if (c == NULL) {
        printf("Could not allocate memory for city.\n");
        exit(1);
    }

    /* Column 1: city name */
    field = getNextField(textLine);
    c->name = strdup(field);

    /* Column 2: city name using ASCII characters */
    field = getNextField(NULL);
    c->city_ascii = strdup(field);

    /* Column 3: state postal code */
    field = getNextField(NULL);
    c->state_id = strdup(field);

    /* Column 4: state name */
    field = getNextField(NULL);
    c->state_name = strdup(field);

    /* Column 5: county FIPS code */
    field = getNextField(NULL);
    c->county_fips = strdup(field);

    /* Column 6: county name */
    field = getNextField(NULL);
    c->county_name = strdup(field);

    /* Column 7: latitude */
    field = getNextField(NULL);
    c->lat = atof(field);

    /* Column 8: longitude */
    field = getNextField(NULL);
    c->lng = atof(field);

    /* Column 9: population */
    field = getNextField(NULL);
    c->population = atoi(field);

    return c;
}


/*
    Task 1B

    Open the file, skip the header,
    read the next 20 city lines,
    and return an array of city pointers.
*/
city **readCityList(char *filename) {
    FILE *fp;
    city **cityArray;
    char line[10000];
    int i;

    fp = fopen(filename, "r");

    if (fp == NULL) {
        printf("Could not open file: %s\n", filename);
        exit(1);
    }

    /*
        Create an array for 20 city pointers.
    */
    cityArray = malloc(20 * sizeof(city *));

    if (cityArray == NULL) {
        printf("Could not allocate memory for city list.\n");
        fclose(fp);
        exit(1);
    }

    /*
        The first line is the header.
        Read it once and ignore it.
    */
    if (fgets(line, 10000, fp) == NULL) {
        printf("Could not read header line.\n");
        fclose(fp);
        exit(1);
    }

    /*
        Read the next 20 lines.
    */
    for (i = 0; i < 20; i++) {
        if (fgets(line, 10000, fp) == NULL) {
            printf("Could not read city line %d.\n", i + 1);
            fclose(fp);
            exit(1);
        }

        cityArray[i] = stringToCity(line);
    }

    fclose(fp);

    return cityArray;
}


/*
    Print one city.
*/
void printCity(city *c) {
    printf("%s %s, population %d\n",
           c->name,
           c->state_id,
           c->population);
}


/*
    Task 1D

    Free one city struct.
    First free the strings.
    Then free the struct itself.
*/
void freeCity(city *c) {
    if (c == NULL) {
        return;
    }

    free(c->name);
    free(c->city_ascii);
    free(c->state_id);
    free(c->state_name);
    free(c->county_fips);
    free(c->county_name);

    free(c);
}


int main(void) {
    city **cityArray;
    char s[100];
    int cityNumber;
    int index;
    int i;

    /*
        For your current VS Code test, your CSV file is in the same folder,
        so use "uscities.csv".

        Before final submission, if the teacher wants the Resources path,
        change this line to:
        cityArray = readCityList("../../Resources/uscities.csv");
    */
    cityArray = readCityList("uscities.csv");

    /*
        Print the first 20 cities to check that reading worked.
    */
    printf("The first 20 cities are:\n");

    for (i = 0; i < 20; i++) {
        printf("%d. %s, population %d\n",
               i + 1,
               cityArray[i]->name,
               cityArray[i]->population);
    }

    /*
        Task 1C

        Read a city number from the user.
    */
    while (1) {
        printf("\nEnter a city number: ");

        /*
            Read from the keyboard.
        */
        if (fgets(s, 100, stdin) == NULL) {
            break;
        }

        /*
            If the user just presses Enter, exit.
        */
        if (s[0] == '\n' || s[0] == '\r') {
            break;
        }

        cityNumber = atoi(s);

        /*
            If the number is out of range, exit.
        */
        if (cityNumber <= 0 || cityNumber > 20) {
            break;
        }

        /*
            City number 1 is cityArray[0].
        */
        index = cityNumber - 1;

        printCity(cityArray[index]);
    }

    /*
        Free each city.
    */
    for (i = 0; i < 20; i++) {
        freeCity(cityArray[i]);
    }

    /*
        Free the array.
    */
    free(cityArray);

    return 0;
}