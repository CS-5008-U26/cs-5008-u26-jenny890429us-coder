/*
 * insertionsort.c
 *
 * this program uses insertion sort to sort arrays.
 * it tests random, sorted, and reverse sorted data
 * and measures how long each sort takes.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_TO_PRINT 100
#define MAX_VALUE 100000000


/* test case data */

int test1[] =       { 3 };
int expected1[] =   { 3 };
int n1 =            1;

int test2[] =       { 5, 3 };
int expected2[] =   { 3, 5 };
int n2 =            2;

int test3[] =       { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
int expected3[] =   { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
int n3 =            10;

int test4[] =       { 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };
int expected4[] =   { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
int n4 =            10;

int test5[] =       { 2, 4, 6, 8, 10, 1, 3, 5, 7, 9 };
int expected5[] =   { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
int n5 =            10;

int test6[] =       { 1, 2, 3, 2, 2 };
int expected6[] =   { 1, 2, 2, 2, 3 };
int n6 =            5;


/*
 * use insertion sort to sort the array.
 * each new value is inserted into the
 * correct position in the sorted part.
 */
void sortarray(int a[], int n) {
    int key;
    int j;

    /*
     * start from the second element because
     * the first element is already sorted.
     */
    for (int i = 1; i < n; i++) {
        key = a[i];
        j = i - 1;

        /*
         * move larger values one position
         * to the right.
         */
        while (j >= 0 && a[j] > key) {
            a[j + 1] = a[j];
            j--;
        }

        /*
         * put the value into its correct position.
         */
        a[j + 1] = key;
    }
}


/*
 * print the values in the array.
 */
void printarray(int a[], int n) {
    int numberToPrint =
        ((n < MAX_TO_PRINT) ? n : MAX_TO_PRINT);

    for (int i = 0; i < numberToPrint; i++) {
        printf("%d ", a[i]);
    }

    printf("\n");
}


/*
 * create an array of random values on the heap.
 */
int *genarray(int numberofelements) {
    int *result =
        malloc(numberofelements * sizeof(int));

    if (result == NULL) {
        printf("malloc failed\n");
    } else {
        for (int i = 0; i < numberofelements; i++) {
            /*
             * combine two random numbers because
             * rand() may return smaller values on windows.
             */
            long long int r1 = rand();
            long long int r2 = rand();

            long long int randomValue =
                (r1 << 14) + (r2 & 0x3fff);

            result[i] =
                (int)(randomValue % MAX_VALUE);
        }
    }

    return result;
}


/*
 * create an array already sorted from 0 to n - 1.
 */
int *gensortedarray(int numberofelements) {
    int *result =
        malloc(numberofelements * sizeof(int));

    if (result == NULL) {
        printf("malloc failed\n");
    } else {
        for (int i = 0; i < numberofelements; i++) {
            result[i] = i;
        }
    }

    return result;
}


/*
 * create an array in reverse order from n - 1 to 0.
 */
int *genreversearray(int numberofelements) {
    int *result =
        malloc(numberofelements * sizeof(int));

    if (result == NULL) {
        printf("malloc failed\n");
    } else {
        for (int i = 0; i < numberofelements; i++) {
            result[i] = numberofelements - 1 - i;
        }
    }

    return result;
}


/*
 * run the sort and print how long it takes.
 */
void timedsort(int a[], int n) {
    clock_t startTime = clock();

    sortarray(a, n);

    clock_t endTime = clock();

    double elapsedTime =
        (double)(endTime - startTime) /
        CLOCKS_PER_SEC;

    printf("Result: ");
    printarray(a, n);

    printf(
        "Elapsed time: %f seconds\n\n",
        elapsedTime
    );
}


/*
 * sort one test case and compare it
 * with the expected result.
 */
void testsort(int a[], int n, int expected[]) {
    printf("Test case: ");
    printarray(a, n);

    sortarray(a, n);

    printf("Result: ");
    printarray(a, n);

    int ok = 1;

    for (int i = 0; ok && i < n; i++) {
        ok = (a[i] == expected[i]);
    }

    printf(
        "%s\n\n",
        ok ? "PASSED" : "FAILED"
    );
}


/*
 * run the test cases first, then test
 * random, sorted, and reverse sorted data.
 */
int main(void) {
    char s[100];
    int nelements;
    int *data;
    int keepgoing;

    srand((unsigned int)time(NULL));

    /* run the required test cases */
    testsort(test1, n1, expected1);
    testsort(test2, n2, expected2);
    testsort(test3, n3, expected3);
    testsort(test4, n4, expected4);
    testsort(test5, n5, expected5);
    testsort(test6, n6, expected6);


    /*
     * random data timing loop
     */
    printf("\nrandom data\n");

    keepgoing = 1;

    while (keepgoing) {
        printf("How many elements? ");

        if (fgets(s, 100, stdin) == NULL) {
            keepgoing = 0;
        } else if (s[0] == '\n') {
            keepgoing = 0;
        } else {
            nelements = atoi(s);

            if (nelements <= 0) {
                printf(
                    "Must be a positive number of elements\n"
                );
            } else {
                data = genarray(nelements);

                if (data != NULL) {
                    timedsort(data, nelements);
                    free(data);
                }
            }
        }
    }


    /*
     * sorted data timing loop
     */
    printf("\nsorted data\n");

    keepgoing = 1;

    while (keepgoing) {
        printf("How many elements? ");

        if (fgets(s, 100, stdin) == NULL) {
            keepgoing = 0;
        } else if (s[0] == '\n') {
            keepgoing = 0;
        } else {
            nelements = atoi(s);

            if (nelements <= 0) {
                printf(
                    "Must be a positive number of elements\n"
                );
            } else {
                data = gensortedarray(nelements);

                if (data != NULL) {
                    timedsort(data, nelements);
                    free(data);
                }
            }
        }
    }


    /*
     * reverse sorted data timing loop
     */
    printf("\nreverse sorted data\n");

    keepgoing = 1;

    while (keepgoing) {
        printf("How many elements? ");

        if (fgets(s, 100, stdin) == NULL) {
            keepgoing = 0;
        } else if (s[0] == '\n') {
            keepgoing = 0;
        } else {
            nelements = atoi(s);

            if (nelements <= 0) {
                printf(
                    "Must be a positive number of elements\n"
                );
            } else {
                data = genreversearray(nelements);

                if (data != NULL) {
                    timedsort(data, nelements);
                    free(data);
                }
            }
        }
    }

    return 0;
}