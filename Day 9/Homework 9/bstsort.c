/*
 * bstsort.c
 *
 * this program sorts an array using a binary search tree.
 * it inserts all array values into the tree, then uses
 * inorder traversal to copy them back into the array.
 * after sorting, all tree nodes are freed.
 *
 * it tests random, sorted, and reverse sorted data.
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
 * each node stores one integer and pointers
 * to the left and right children.
 */
typedef struct bstnode {
    int value;
    struct bstnode *left;
    struct bstnode *right;
} BstNode;


/*
 * create a new node and initialize
 * both child pointers to null.
 */
BstNode *createBstNode(int value) {
    BstNode *newNode = malloc(sizeof(BstNode));

    if (newNode == NULL) {
        printf("malloc failed\n");
        exit(EXIT_FAILURE);
    }

    newNode->value = value;
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}


/*
 * insert one value into the bst.
 * smaller values go left, and larger
 * or equal values go right.
 */
BstNode *insertBst(BstNode *root, int value) {
    if (root == NULL) {
        return createBstNode(value);
    }

    if (value < root->value) {
        root->left = insertBst(root->left, value);
    } else {
        root->right = insertBst(root->right, value);
    }

    return root;
}


/*
 * use inorder traversal to copy the values
 * from the bst back into the array.
 */
void bstToArray(BstNode *root, int a[], int *index) {
    if (root == NULL) {
        return;
    }

    bstToArray(root->left, a, index);

    a[*index] = root->value;
    (*index)++;

    bstToArray(root->right, a, index);
}


/*
 * free every node in the tree.
 * the children need to be freed before
 * the current node.
 */
void freeBst(BstNode *root) {
    if (root == NULL) {
        return;
    }

    freeBst(root->left);
    freeBst(root->right);

    free(root);
}


/*
 * sort the array using bst sort.
 */
void sortarray(int a[], int n) {
    BstNode *root = NULL;
    int index = 0;

    /* build the bst from the array */
    for (int i = 0; i < n; i++) {
        root = insertBst(root, a[i]);
    }

    /* copy the values back in sorted order */
    bstToArray(root, a, &index);

    /* free the bst after sorting */
    freeBst(root);
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

    printf("Elapsed time: %f seconds\n\n",
           elapsedTime);
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

    printf("%s\n\n",
           ok ? "PASSED" : "FAILED");
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

    /* run all test cases */
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
                printf("Must be a positive number of elements\n");
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
                printf("Must be a positive number of elements\n");
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
                printf("Must be a positive number of elements\n");
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