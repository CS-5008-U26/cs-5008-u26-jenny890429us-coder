#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// This struct stores information for one candy.
typedef struct Candy {
    char *name;

    int chocolate;
    int fruity;
    int caramel;
    int peanutalmondy;
    int nougat;
    int crispedricewafer;
    int hard;
    int bar;
    int pluribus;

    double sugarpercent;
    double pricepercent;
    double winpercent;
} Candy;


// This function removes the newline at the end of a string.
void killNewline(char *str) {
    int len;

    len = strlen(str);

    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
}


// This function copies a string onto the heap.
char *copyString(char *str) {
    char *newStr;

    newStr = malloc(strlen(str) + 1);

    if (newStr == NULL) {
        printf("Memory error.\n");
        exit(1);
    }

    strcpy(newStr, str);

    return newStr;
}


// This function prints a string in uppercase.
void printUpper(char *str) {
    int i;

    for (i = 0; str[i] != '\0'; i++) {
        printf("%c", toupper(str[i]));
    }
}


// This function prints a string in lowercase.
void printLower(char *str) {
    int i;

    for (i = 0; str[i] != '\0'; i++) {
        printf("%c", tolower(str[i]));
    }
}


// This function creates one Candy struct from one line of the CSV file.
Candy *makeCandy(char *line) {
    Candy *candy;
    char *token;

    candy = malloc(sizeof(Candy));

    if (candy == NULL) {
        printf("Memory error.\n");
        exit(1);
    }

    killNewline(line);

    token = strtok(line, ",");
    candy->name = copyString(token);

    token = strtok(NULL, ",");
    candy->chocolate = atoi(token);

    token = strtok(NULL, ",");
    candy->fruity = atoi(token);

    token = strtok(NULL, ",");
    candy->caramel = atoi(token);

    token = strtok(NULL, ",");
    candy->peanutalmondy = atoi(token);

    token = strtok(NULL, ",");
    candy->nougat = atoi(token);

    token = strtok(NULL, ",");
    candy->crispedricewafer = atoi(token);

    token = strtok(NULL, ",");
    candy->hard = atoi(token);

    token = strtok(NULL, ",");
    candy->bar = atoi(token);

    token = strtok(NULL, ",");
    candy->pluribus = atoi(token);

    token = strtok(NULL, ",");
    candy->sugarpercent = atof(token);

    token = strtok(NULL, ",");
    candy->pricepercent = atof(token);

    token = strtok(NULL, ",");
    candy->winpercent = atof(token);

    return candy;
}


// This function prints all candy names.
void printAllCandies(Candy **candies, int count) {
    int i;

    printf("All candies:\n");

    for (i = 0; i < count; i++) {
        printf("%s\n", candies[i]->name);
    }
}


// This function does Task 2.
void printChocolateCandies(Candy **candies, int count) {
    int i;
    int chocolateCount = 0;
    int chocolateCaramelCount = 0;
    double percent;

    printf("\nChocolate candies:\n");

    for (i = 0; i < count; i++) {
        if (candies[i]->chocolate == 1) {
            chocolateCount++;

            if (candies[i]->caramel == 1) {
                chocolateCaramelCount++;
                printUpper(candies[i]->name);
                printf("\n");
            } else {
                printLower(candies[i]->name);
                printf("\n");
            }
        }
    }

    if (chocolateCount > 0) {
        percent = (double) chocolateCaramelCount / chocolateCount * 100.0;
        printf("\nPercent of chocolate candies with caramel: %.2f%%\n", percent);
    }
}


// This function prints one summary line.
void printSummaryLine(char *label, double sugarTotal, double priceTotal,
                      double winTotal, int count) {
    if (count > 0) {
        printf("%-20s sugar average: %.3f  price average: %.3f  win average: %.3f\n",
               label,
               sugarTotal / count,
               priceTotal / count,
               winTotal / count);
    } else {
        printf("%-20s no candies found\n", label);
    }
}


// This function checks one attribute and prints its summary.
void printAttributeSummary(Candy **candies, int count, char *label, int attrNumber) {
    int i;
    int matchCount = 0;
    int hasAttribute;

    double sugarTotal = 0;
    double priceTotal = 0;
    double winTotal = 0;

    for (i = 0; i < count; i++) {
        hasAttribute = 0;

        if (attrNumber == 1) {
            hasAttribute = candies[i]->chocolate;
        } else if (attrNumber == 2) {
            hasAttribute = candies[i]->fruity;
        } else if (attrNumber == 3) {
            hasAttribute = candies[i]->caramel;
        } else if (attrNumber == 4) {
            hasAttribute = candies[i]->peanutalmondy;
        } else if (attrNumber == 5) {
            hasAttribute = candies[i]->nougat;
        } else if (attrNumber == 6) {
            hasAttribute = candies[i]->crispedricewafer;
        } else if (attrNumber == 7) {
            hasAttribute = candies[i]->hard;
        } else if (attrNumber == 8) {
            hasAttribute = candies[i]->bar;
        } else if (attrNumber == 9) {
            hasAttribute = candies[i]->pluribus;
        }

        if (hasAttribute == 1) {
            matchCount++;
            sugarTotal = sugarTotal + candies[i]->sugarpercent;
            priceTotal = priceTotal + candies[i]->pricepercent;
            winTotal = winTotal + candies[i]->winpercent;
        }
    }

    printSummaryLine(label, sugarTotal, priceTotal, winTotal, matchCount);
}


// This function prints summaries for all attributes.
void printAllAttributeSummaries(Candy **candies, int count) {
    printf("\nSummary by attribute:\n");

    printAttributeSummary(candies, count, "chocolate", 1);
    printAttributeSummary(candies, count, "fruity", 2);
    printAttributeSummary(candies, count, "caramel", 3);
    printAttributeSummary(candies, count, "peanutalmondy", 4);
    printAttributeSummary(candies, count, "nougat", 5);
    printAttributeSummary(candies, count, "crispedricewafer", 6);
    printAttributeSummary(candies, count, "hard", 7);
    printAttributeSummary(candies, count, "bar", 8);
    printAttributeSummary(candies, count, "pluribus", 9);
}


// This function prints the summary for candies above average sugar and price.
void printAboveAverageSummaries(Candy **candies, int count) {
    int i;

    double sugarTotal = 0;
    double priceTotal = 0;

    double avgSugar;
    double avgPrice;

    double highSugarSugarTotal = 0;
    double highSugarPriceTotal = 0;
    double highSugarWinTotal = 0;
    int highSugarCount = 0;

    double highPriceSugarTotal = 0;
    double highPricePriceTotal = 0;
    double highPriceWinTotal = 0;
    int highPriceCount = 0;

    for (i = 0; i < count; i++) {
        sugarTotal = sugarTotal + candies[i]->sugarpercent;
        priceTotal = priceTotal + candies[i]->pricepercent;
    }

    avgSugar = sugarTotal / count;
    avgPrice = priceTotal / count;

    for (i = 0; i < count; i++) {
        if (candies[i]->sugarpercent > avgSugar) {
            highSugarCount++;
            highSugarSugarTotal = highSugarSugarTotal + candies[i]->sugarpercent;
            highSugarPriceTotal = highSugarPriceTotal + candies[i]->pricepercent;
            highSugarWinTotal = highSugarWinTotal + candies[i]->winpercent;
        }

        if (candies[i]->pricepercent > avgPrice) {
            highPriceCount++;
            highPriceSugarTotal = highPriceSugarTotal + candies[i]->sugarpercent;
            highPricePriceTotal = highPricePriceTotal + candies[i]->pricepercent;
            highPriceWinTotal = highPriceWinTotal + candies[i]->winpercent;
        }
    }

    printf("\nSummary for above average groups:\n");

    printSummaryLine("above avg sugar",
                     highSugarSugarTotal,
                     highSugarPriceTotal,
                     highSugarWinTotal,
                     highSugarCount);

    printSummaryLine("above avg price",
                     highPriceSugarTotal,
                     highPricePriceTotal,
                     highPriceWinTotal,
                     highPriceCount);
}


// This function frees memory.
void freeCandies(Candy **candies, int count) {
    int i;

    for (i = 0; i < count; i++) {
        free(candies[i]->name);
        free(candies[i]);
    }
}


int main(void) {
    FILE *file;
    Candy **candies;
    char line[300];
    int count = 0;

    char s[100];

    candies = malloc(sizeof(Candy *) * 200);

    if (candies == NULL) {
        printf("Memory error.\n");
        return 1;
    }

    file = fopen("candy-data.csv", "r");

    if (file == NULL) {
        printf("Could not open candy-data.csv\n");
        free(candies);
        return 1;
    }

    // Read and ignore the header line.
    fgets(line, 300, file);

    // Read the rest of the file.
    while (fgets(line, 300, file) != NULL && count < 200) {
        candies[count] = makeCandy(line);
        count++;
    }

    fclose(file);

    printAllCandies(candies, count);

    printChocolateCandies(candies, count);

    printAllAttributeSummaries(candies, count);

    printAboveAverageSummaries(candies, count);

    freeCandies(candies, count);
    free(candies);

    printf("\nPress Enter to exit.");
    fgets(s, 100, stdin);

    return 0;
}