#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
    This lab practices linked lists and prime numbers.
    I use long long int because the instructions say the numbers
    and divisors should be long long int.
*/

typedef struct intNode
{
    long long int value;
    struct intNode *next;
} node;

/*
    This function creates one new node.
    It stores x in value and sets next to NULL.
*/
node *createNode(long long int x)
{
    node *newNode;

    newNode = (node *)malloc(sizeof(node));

    if (newNode == NULL)
    {
        printf("Memory allocation failed.\n");
        exit(1);
    }

    newNode->value = x;
    newNode->next = NULL;

    return newNode;
}

/*
    This function adds a node to the front of the list.
*/
node *insertFront(node *list, long long int x)
{
    node *newNode;

    newNode = createNode(x);

    newNode->next = list;
    list = newNode;

    return list;
}

/*
    This function adds a node to the end of the list.
*/
node *insertLast(node *list, long long int x)
{
    node *newNode;
    node *current;

    newNode = createNode(x);

    if (list == NULL)
    {
        return newNode;
    }

    current = list;

    while (current->next != NULL)
    {
        current = current->next;
    }

    current->next = newNode;

    return list;
}

/*
    This is the Task 1A prime test.
    It tries dividing by all numbers from 2 up to sqrt(x).
*/
int isPrimeSlow(long long int x)
{
    long long int d;

    if (x < 2)
    {
        return 0;
    }

    for (d = 2; d <= x / d; d++)
    {
        if (x % d == 0)
        {
            return 0;
        }
    }

    return 1;
}

/*
    This checks if x is prime using a linked list of primes.

    For insertFront, the list is in reverse order:
    largest prime first, smallest prime last.
    So we cannot stop early. We just check the whole list.
*/
int isPrimeUsingListFront(long long int x, node *primes)
{
    node *current;

    if (x < 2)
    {
        return 0;
    }

    current = primes;

    while (current != NULL)
    {
        if (current->value <= x / current->value)
        {
            if (x % current->value == 0)
            {
                return 0;
            }
        }

        current = current->next;
    }

    return 1;
}

/*
    This checks if x is prime using a linked list of primes.

    For insertLast, the list is in normal order:
    smallest prime first, largest prime last.
    This lets us stop early after sqrt(x).
*/
int isPrimeUsingListLast(long long int x, node *primes)
{
    node *current;

    if (x < 2)
    {
        return 0;
    }

    current = primes;

    while (current != NULL)
    {
        if (current->value > x / current->value)
        {
            break;
        }

        if (x % current->value == 0)
        {
            return 0;
        }

        current = current->next;
    }

    return 1;
}

/*
    Task 1A:
    Find primes for about 0.5 seconds using the slow method.
*/
long long int task1A()
{
    clock_t start;
    clock_t end;
    double seconds;

    long long int candidate;
    long long int lastPrime;

    start = clock();

    candidate = 2;
    lastPrime = 0;

    while (1)
    {
        if (isPrimeSlow(candidate))
        {
            lastPrime = candidate;

            end = clock();
            seconds = (double)(end - start) / CLOCKS_PER_SEC;

            if (seconds >= 0.5)
            {
                break;
            }
        }

        candidate++;
    }

    return lastPrime;
}

/*
    Task 1B:
    Find primes for about 0.5 seconds.
    Store each prime in a linked list using insertFront.
*/
long long int task1B()
{
    clock_t start;
    clock_t end;
    double seconds;

    long long int candidate;
    long long int lastPrime;

    node *primes;

    start = clock();

    candidate = 2;
    lastPrime = 0;
    primes = NULL;

    while (1)
    {
        if (isPrimeUsingListFront(candidate, primes))
        {
            lastPrime = candidate;

            primes = insertFront(primes, candidate);

            end = clock();
            seconds = (double)(end - start) / CLOCKS_PER_SEC;

            if (seconds >= 0.5)
            {
                break;
            }
        }

        candidate++;
    }

    return lastPrime;
}

/*
    Task 1C:
    Find primes for about 0.5 seconds.
    Store each prime in a linked list using insertLast.
*/
long long int task1C()
{
    clock_t start;
    clock_t end;
    double seconds;

    long long int candidate;
    long long int lastPrime;

    node *primes;

    start = clock();

    candidate = 2;
    lastPrime = 0;
    primes = NULL;

    while (1)
    {
        if (isPrimeUsingListLast(candidate, primes))
        {
            lastPrime = candidate;

            primes = insertLast(primes, candidate);

            end = clock();
            seconds = (double)(end - start) / CLOCKS_PER_SEC;

            if (seconds >= 0.5)
            {
                break;
            }
        }

        candidate++;
    }

    return lastPrime;
}

/*
    This function prints a linked list.
*/
void printList(node *list)
{
    node *current;

    current = list;

    while (current != NULL)
    {
        printf("%lld ", current->value);
        current = current->next;
    }

    printf("\n");
}

/*
    This checks if the second digit is bigger than the first digit.

    Example:
    13 -> first digit is 1, second digit is 3, true
    31 -> first digit is 3, second digit is 1, false
    157 -> first digit is 1, second digit is 5, true
*/
int secondDigitBigger(long long int x)
{
    int firstDigit;
    int secondDigit;

    if (x < 10)
    {
        return 0;
    }

    while (x >= 100)
    {
        x = x / 10;
    }

    firstDigit = x / 10;
    secondDigit = x % 10;

    if (secondDigit > firstDigit)
    {
        return 1;
    }

    return 0;
}

/*
    This creates a list with the first 100 prime numbers.
*/
node *first100Primes()
{
    node *list;
    long long int candidate;
    int count;

    list = NULL;
    candidate = 2;
    count = 0;

    while (count < 100)
    {
        if (isPrimeUsingListLast(candidate, list))
        {
            list = insertLast(list, candidate);
            count++;
        }

        candidate++;
    }

    return list;
}

/*
    This creates a new list that only contains primes
    whose second digit is bigger than the first digit.
*/
node *makeSecondDigitList(node *primeList)
{
    node *newList;
    node *current;

    newList = NULL;
    current = primeList;

    while (current != NULL)
    {
        if (secondDigitBigger(current->value))
        {
            newList = insertLast(newList, current->value);
        }

        current = current->next;
    }

    return newList;
}

/*
    This reverses a linked list.
*/
node *reverseList(node *list)
{
    node *previous;
    node *current;
    node *nextNode;

    previous = NULL;
    current = list;

    while (current != NULL)
    {
        nextNode = current->next;
        current->next = previous;
        previous = current;
        current = nextNode;
    }

    return previous;
}

/*
    This frees memory used by a linked list.
*/
void freeList(node *list)
{
    node *current;
    node *nextNode;

    current = list;

    while (current != NULL)
    {
        nextNode = current->next;
        free(current);
        current = nextNode;
    }
}

int main()
{
    char s[100];

    long long int lastA;
    long long int lastB;
    long long int lastC;

    node *primeList;
    node *secondDigitList;
    node *reversedList;

    printf("Task 1A:\n");
    lastA = task1A();
    printf("Last prime found in 0.5 seconds using slow method: %lld\n\n", lastA);

    printf("Task 1B:\n");
    lastB = task1B();
    printf("Last prime found in 0.5 seconds using insertFront list: %lld\n\n", lastB);

    printf("Task 1C:\n");
    lastC = task1C();
    printf("Last prime found in 0.5 seconds using insertLast list: %lld\n\n", lastC);

    printf("Task 2A:\n");
    primeList = first100Primes();
    secondDigitList = makeSecondDigitList(primeList);

    printf("Prime numbers whose second digit is bigger than the first digit:\n");
    printList(secondDigitList);
    printf("\n");

    printf("Task 2B:\n");
    reversedList = reverseList(secondDigitList);

    printf("Reversed list:\n");
    printList(reversedList);
    printf("\n");

    freeList(primeList);
    freeList(reversedList);

    printf("Press Enter to exit.\n");
    fgets(s, 100, stdin);

    return 0;
}