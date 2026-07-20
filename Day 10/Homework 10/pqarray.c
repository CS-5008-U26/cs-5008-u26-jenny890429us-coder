/*
 * pqarray.c
 *
 * Homework 10 - Task 1
 *
 * This program implements a priority queue using a sorted
 * dynamic array.
 *
 * After a group of random numbers is added, the entire
 * priority queue is sorted from smallest to largest.
 *
 * When numbers are removed, they are taken from the front
 * of the array. The remaining entries are then copied
 * forward one time, and the logical queue size is reduced.
 *
 * Normal mode:
 *     ./pqarray
 *
 * Benchmark mode:
 *     ./pqarray --benchmark
 *
 * 10-Second N values:
 * Add:    56000000
 * Remove: Could not reach 10 seconds before memory limit
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <limits.h>

#define INITIAL_CAPACITY 10
#define MAX_VALUE 100000000


/*
 * Compare two integers for qsort().
 */
int compareInts(const void *first, const void *second) {
    int a = *(const int *)first;
    int b = *(const int *)second;

    if (a < b) {
        return -1;
    }

    if (a > b) {
        return 1;
    }

    return 0;
}


/*
 * Generate an array containing random integers.
 */
int *genarray(int numberOfElements) {
    int *result = NULL;

    if (numberOfElements > 0) {
        result = malloc(
            (size_t)numberOfElements * sizeof(int)
        );

        if (result == NULL) {
            fprintf(stderr, "malloc failed\n");
            return NULL;
        }
    }

    for (int i = 0; i < numberOfElements; i++) {
        long long r1 = rand();
        long long r2 = rand();

        long long randomValue =
            (r1 << 14) + (r2 & 0x3fff);

        result[i] =
            (int)(randomValue % MAX_VALUE);
    }

    return result;
}


/*
 * Increase the backing-array capacity when necessary.
 */
int ensureCapacity(
    int **queue,
    int *capacity,
    int needed
) {
    if (needed <= *capacity) {
        return 1;
    }

    int newCapacity = *capacity;

    while (newCapacity < needed) {
        if (newCapacity > INT_MAX / 2) {
            newCapacity = needed;
            break;
        }

        newCapacity *= 2;
    }

    int *newQueue = realloc(
        *queue,
        (size_t)newCapacity * sizeof(int)
    );

    if (newQueue == NULL) {
        fprintf(stderr, "realloc failed\n");
        return 0;
    }

    *queue = newQueue;
    *capacity = newCapacity;

    return 1;
}


/*
 * Read a nonnegative integer.
 *
 * Return values:
 *   1  valid number
 *   0  user pressed ENTER or input ended
 *  -1  invalid input
 */
int readNumber(const char *prompt, int *number) {
    char input[100];
    char *end;
    long value;

    printf("%s", prompt);
    fflush(stdout);

    if (fgets(input, sizeof(input), stdin) == NULL) {
        return 0;
    }

    if (input[0] == '\n') {
        return 0;
    }

    value = strtol(input, &end, 10);

    if (end == input) {
        printf("Please enter a valid number.\n\n");
        return -1;
    }

    while (*end == ' ' || *end == '\t') {
        end++;
    }

    if (*end != '\n' && *end != '\0') {
        printf("Please enter a valid number.\n\n");
        return -1;
    }

    if (value < 0 || value > INT_MAX) {
        printf("Please enter 0 or a positive integer.\n\n");
        return -1;
    }

    *number = (int)value;

    return 1;
}


int main(int argc, char *argv[]) {
    int benchmarkMode = 0;

    /*
     * In benchmark mode, removed numbers are not printed.
     * This prevents terminal output from affecting timing.
     */
    if (argc > 1 &&
        strcmp(argv[1], "--benchmark") == 0) {

        benchmarkMode = 1;

        printf(
            "Benchmark mode: removed numbers will not "
            "be printed.\n\n"
        );
    }

    /*
     * Create the initial backing array.
     */
    int *queue = malloc(
        INITIAL_CAPACITY * sizeof(int)
    );

    if (queue == NULL) {
        fprintf(stderr, "malloc failed\n");
        return 1;
    }

    int size = 0;
    int capacity = INITIAL_CAPACITY;

    srand((unsigned int)time(NULL));

    while (1) {
        int numberToAdd;
        int numberToRemove;
        int inputResult;

        /*
         * Ask how many numbers to add.
         */
        do {
            inputResult = readNumber(
                "How many numbers to add: ",
                &numberToAdd
            );
        } while (inputResult == -1);

        /*
         * Stop when the user presses ENTER.
         */
        if (inputResult == 0) {
            break;
        }

        /*
         * Prevent size + numberToAdd from overflowing.
         */
        if (numberToAdd > INT_MAX - size) {
            fprintf(
                stderr,
                "Too many numbers requested.\n"
            );

            free(queue);
            return 1;
        }

        /*
         * Generate the new random numbers before timing
         * the priority-queue add operation.
         */
        int *newNumbers = genarray(numberToAdd);

        if (newNumbers == NULL &&
            numberToAdd > 0) {

            free(queue);
            return 1;
        }

        clock_t addStart = clock();

        /*
         * Increase the backing array if more room is needed.
         */
        if (!ensureCapacity(
                &queue,
                &capacity,
                size + numberToAdd
            )) {

            free(newNumbers);
            free(queue);
            return 1;
        }

        /*
         * Add the new numbers to the end of the array.
         */
        if (numberToAdd > 0) {
            memcpy(
                queue + size,
                newNumbers,
                (size_t)numberToAdd * sizeof(int)
            );
        }

        size += numberToAdd;

        /*
         * Sort the whole priority queue after adding.
         */
        if (size > 1) {
            qsort(
                queue,
                (size_t)size,
                sizeof(int),
                compareInts
            );
        }

        clock_t addEnd = clock();

        free(newNumbers);

        double addElapsed =
            (double)(addEnd - addStart) /
            CLOCKS_PER_SEC;

        printf(
            "Elapsed time for adding: %.6f seconds\n",
            addElapsed
        );

        printf(
            "Current queue size: %d\n\n",
            size
        );

        /*
         * Stop if the priority queue is empty.
         */
        if (size == 0) {
            printf("Priority queue is empty.\n");
            break;
        }

        /*
         * Ask how many numbers to remove.
         */
        do {
            inputResult = readNumber(
                "How many numbers to remove: ",
                &numberToRemove
            );
        } while (inputResult == -1);

        /*
         * Stop when the user presses ENTER.
         */
        if (inputResult == 0) {
            break;
        }

        /*
         * Do not remove more numbers than the queue contains.
         */
        int actualRemove = numberToRemove;

        if (actualRemove > size) {
            actualRemove = size;
        }

        /*
         * Print the values at the front before removing them.
         *
         * The queue is already sorted, so these values are
         * printed from smallest to largest.
         *
         * Printing is skipped during benchmark mode.
         */
        if (!benchmarkMode) {
            for (int i = 0; i < actualRemove; i++) {
                printf("%d ", queue[i]);
            }

            if (actualRemove > 0) {
                printf("\n");
            }
        }

        clock_t removeStart = clock();

        /*
         * Calculate how many entries remain.
         */
        int remaining = size - actualRemove;

        /*
         * Shift the remaining entries forward one time.
         *
         * For example, if three entries are removed:
         *
         * Before:
         * [removed][removed][removed][keep][keep]
         *
         * After:
         * [keep][keep]
         */
        if (remaining > 0) {
            memmove(
                queue,
                queue + actualRemove,
                (size_t)remaining * sizeof(int)
            );
        }

        /*
         * Reduce the logical size of the queue.
         */
        size = remaining;

        clock_t removeEnd = clock();

        double removeElapsed =
            (double)(removeEnd - removeStart) /
            CLOCKS_PER_SEC;

        printf(
            "Elapsed time for removing: %.6f seconds\n",
            removeElapsed
        );

        printf(
            "Current queue size: %d\n\n",
            size
        );

        /*
         * Stop when the priority queue becomes empty.
         */
        if (size == 0) {
            printf("Priority queue is empty.\n");
            break;
        }
    }

    free(queue);

    return 0;
}