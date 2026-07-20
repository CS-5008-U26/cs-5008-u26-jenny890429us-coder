/*
 * pqheap.c
 *
 * Homework 10 - Task 2
 *
 * This program implements a priority queue using a min-heap.
 * The smallest value is always stored at the root.
 *
 * Each new number is inserted at the end of the heap and
 * moved upward using heapifyUp().
 *
 * Each removed number is taken from the root. The last
 * element is moved to the root, the heap size is reduced,
 * and heapifyDown() restores the min-heap.
 *
 * Normal mode:
 *     ./pqheap
 *
 * Benchmark mode:
 *     ./pqheap --benchmark
 *
 * 10-Second N values:
 * Add:    500000000
 * Remove: 15000000
 * 
 * Conclusion:
 * The heap was faster for adding numbers, while the sorted array
was faster for removing a large group of numbers.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <limits.h>

#define INITIAL_CAPACITY 10
#define MAX_VALUE 100000000


/*
 * Exchange two integers.
 */
void swap(int *first, int *second) {
    int temp = *first;
    *first = *second;
    *second = temp;
}


/*
 * Move a newly inserted value upward until the
 * min-heap property is restored.
 */
void heapifyUp(int *heap, int index) {
    while (index > 0) {
        int parent = (index - 1) / 2;

        /*
         * Stop when the parent is already smaller than
         * or equal to the child.
         */
        if (heap[parent] <= heap[index]) {
            break;
        }

        swap(&heap[parent], &heap[index]);

        index = parent;
    }
}


/*
 * Move the value at index downward until the
 * min-heap property is restored.
 */
void heapifyDown(
    int *heap,
    int size,
    int index
) {
    while (1) {
        int leftChild = 2 * index + 1;
        int rightChild = 2 * index + 2;
        int smallest = index;

        /*
         * Check whether the left child is smaller.
         */
        if (leftChild < size &&
            heap[leftChild] < heap[smallest]) {

            smallest = leftChild;
        }

        /*
         * Check whether the right child is smaller.
         */
        if (rightChild < size &&
            heap[rightChild] < heap[smallest]) {

            smallest = rightChild;
        }

        /*
         * Stop when the current value is already the
         * smallest of the three.
         */
        if (smallest == index) {
            break;
        }

        swap(&heap[index], &heap[smallest]);

        index = smallest;
    }
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
    int **heap,
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

    int *newHeap = realloc(
        *heap,
        (size_t)newCapacity * sizeof(int)
    );

    if (newHeap == NULL) {
        fprintf(stderr, "realloc failed\n");
        return 0;
    }

    *heap = newHeap;
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

    /*
     * Stop when the user presses ENTER.
     */
    if (input[0] == '\n') {
        return 0;
    }

    value = strtol(input, &end, 10);

    if (end == input) {
        printf("Please enter a valid number.\n\n");
        return -1;
    }

    /*
     * Skip spaces after the number.
     */
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
     * Benchmark mode does not print removed numbers.
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
     * Allocate the initial backing array.
     */
    int *heap = malloc(
        INITIAL_CAPACITY * sizeof(int)
    );

    if (heap == NULL) {
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

        if (inputResult == 0) {
            break;
        }

        /*
         * Prevent integer overflow.
         */
        if (numberToAdd > INT_MAX - size) {
            fprintf(
                stderr,
                "Too many numbers requested.\n"
            );

            free(heap);
            return 1;
        }

        /*
         * Generate the random numbers before timing the
         * priority-queue insertion operations.
         */
        int *newNumbers = genarray(numberToAdd);

        if (newNumbers == NULL &&
            numberToAdd > 0) {

            free(heap);
            return 1;
        }

        clock_t addStart = clock();

        /*
         * Make sure the backing array is large enough.
         */
        if (!ensureCapacity(
                &heap,
                &capacity,
                size + numberToAdd
            )) {

            free(newNumbers);
            free(heap);
            return 1;
        }

        /*
         * Insert each new number separately.
         *
         * The new value is first placed at the end of the
         * heap. heapifyUp() then restores the min-heap.
         */
        for (int i = 0; i < numberToAdd; i++) {
            heap[size] = newNumbers[i];

            heapifyUp(heap, size);

            size++;
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
            "Current heap size: %d\n\n",
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

        if (inputResult == 0) {
            break;
        }

        /*
         * Do not remove more numbers than the heap contains.
         */
        int actualRemove = numberToRemove;

        if (actualRemove > size) {
            actualRemove = size;
        }

        clock_t removeStart = clock();

        /*
         * Remove the minimum value one at a time.
         */
        for (int i = 0; i < actualRemove; i++) {
            /*
             * The root contains the smallest value.
             */
            int removedValue = heap[0];

            /*
             * Move the final heap entry to the root.
             */
            heap[0] = heap[size - 1];

            /*
             * Reduce the logical heap size.
             */
            size--;

            /*
             * Restore the min-heap when entries remain.
             */
            if (size > 0) {
                heapifyDown(heap, size, 0);
            }

            /*
             * Printing is skipped in benchmark mode.
             */
            if (!benchmarkMode) {
                printf("%d ", removedValue);
            }
        }

        clock_t removeEnd = clock();

        if (!benchmarkMode &&
            actualRemove > 0) {

            printf("\n");
        }

        double removeElapsed =
            (double)(removeEnd - removeStart) /
            CLOCKS_PER_SEC;

        printf(
            "Elapsed time for removing: %.6f seconds\n",
            removeElapsed
        );

        printf(
            "Current heap size: %d\n\n",
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

    free(heap);

    return 0;
}