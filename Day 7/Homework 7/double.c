#include <stdio.h>     
#include <stdlib.h>     
#include <string.h>     

/*
    Homework 7 Task 2
    Doubly linked list of cities.

    This program reads the first 20 cities from uscities.csv.
    Each city is stored in a city struct.
    Each city struct is stored inside a generic doubly linked list node.
*/

typedef struct city {
    char *name;          // city name
    char *city_ascii;    // city ascii name
    char *state_id;      // state abbreviation
    char *state_name;    // full state name
    char *county_fips;   // county fips code
    char *county_name;   // county name
    double lat;          // latitude
    double lng;          // longitude
    int population;      // city population
} city;

/*
    Generic doubly linked list node.
    data is void *, so it can store any kind of pointer.
*/
typedef struct doubleNode {
    void *data;                 // generic data pointer
    struct doubleNode *next;    // next node
    struct doubleNode *prev;    // previous node
} dNode;


/*
    Copy a string into new memory.
    I use this instead of strdup to avoid compiler problems.
*/
char *copyString(char *text) {
    char *copy;                         // new string pointer

    if (text == NULL) {                 // check bad argument
        return NULL;                    // return NULL if text is bad
    }

    copy = malloc(strlen(text) + 1);    // make memory for the string and '\0'

    if (copy == NULL) {                 // check if malloc failed
        printf("Could not allocate memory for string.\n");
        exit(1);
    }

    strcpy(copy, text);                 // copy text into new memory

    return copy;                        // return the copied string
}


/*
    Remove newline after using fgets.
*/
void killNewline(char *s) {
    if (s == NULL) {                    // check bad argument
        return;
    }

    s[strcspn(s, "\r\n")] = '\0';       // replace newline with end of string
}


/*
    Remove quotes and newline characters from a CSV field.
*/
void removeQuotes(char *field) {
    int len;                            // length of the field

    if (field == NULL) {                // check bad argument
        return;
    }

    field[strcspn(field, "\r\n")] = '\0'; // remove newline

    len = strlen(field);                // get field length

    if (len > 0 && field[0] == '"') {   // check first quote
        memmove(field, field + 1, len); // remove first quote
    }

    len = strlen(field);                // get new length

    if (len > 0 && field[len - 1] == '"') { // check last quote
        field[len - 1] = '\0';          // remove last quote
    }
}


/*
    Get the next field from a CSV line.
    First call uses the line. Later calls use NULL.
*/
char *getNextField(char *line) {
    char *field;                        // one CSV field

    field = strtok(line, ",");          // split line by comma

    if (field == NULL) {                // check missing field
        printf("Error: missing field in CSV line.\n");
        exit(1);
    }

    removeQuotes(field);                // clean the field

    return field;                       // return the field
}


/*
    Convert one CSV line into one city struct.
*/
city *stringToCity(char *textLine) {
    city *c;                            // city pointer
    char *field;                        // CSV field pointer

    c = malloc(sizeof(city));           // make memory for one city

    if (c == NULL) {                    // check if malloc failed
        printf("Could not allocate memory for city.\n");
        exit(1);
    }

    field = getNextField(textLine);     // get city name
    c->name = copyString(field);        // save city name

    field = getNextField(NULL);         // get ascii name
    c->city_ascii = copyString(field);  // save ascii name

    field = getNextField(NULL);         // get state abbreviation
    c->state_id = copyString(field);    // save state abbreviation

    field = getNextField(NULL);         // get full state name
    c->state_name = copyString(field);  // save full state name

    field = getNextField(NULL);         // get county fips
    c->county_fips = copyString(field); // save county fips

    field = getNextField(NULL);         // get county name
    c->county_name = copyString(field); // save county name

    field = getNextField(NULL);         // get latitude
    c->lat = atof(field);               // convert latitude to double

    field = getNextField(NULL);         // get longitude
    c->lng = atof(field);               // convert longitude to double

    field = getNextField(NULL);         // get population
    c->population = atoi(field);        // convert population to int

    return c;                           // return the new city
}


/*
    Print one city in the homework format.
*/
void printCity(city *c) {
    if (c == NULL) {                    // check bad argument
        return;
    }

    printf("%s %s, population %d\n", c->name, c->state_id, c->population);
}


/*
    Free one city struct.
*/
void freeCity(city *c) {
    if (c == NULL) {                    // check bad argument
        return;
    }

    free(c->name);                      // free city name
    free(c->city_ascii);                // free ascii name
    free(c->state_id);                  // free state abbreviation
    free(c->state_name);                // free full state name
    free(c->county_fips);               // free county fips
    free(c->county_name);               // free county name
    free(c);                            // free city struct
}


/*
    Create one doubly linked list node.
*/
dNode *createDNode(city *c) {
    dNode *node;                        // new node pointer

    if (c == NULL) {                    // check bad city pointer
        return NULL;
    }

    node = malloc(sizeof(dNode));       // make memory for one node

    if (node == NULL) {                 // check if malloc failed
        printf("Could not allocate memory for node.\n");
        exit(1);
    }

    node->data = c;                     // store city pointer in data
    node->next = NULL;                  // node is not connected to next yet
    node->prev = NULL;                  // node is not connected to prev yet

    return node;                        // return new node
}


/*
    Add a node to the front of the doubly linked list.
*/
void addDNodeFront(dNode **list, dNode *node) {
    if (list == NULL || node == NULL) { // check bad arguments
        return;
    }

    node->prev = NULL;                  // new first node has no previous node
    node->next = *list;                 // new node points to old head

    if (*list != NULL) {                // check if old list is not empty
        (*list)->prev = node;           // old head points back to new node
    }

    *list = node;                       // new node becomes head
}


/*
    Add a node to the end of the doubly linked list.
    This keeps city order the same as the CSV file.
*/
void addDNodeEnd(dNode **list, dNode *node) {
    dNode *current;                     // pointer used to walk through list

    if (list == NULL || node == NULL) { // check bad arguments
        return;
    }

    node->next = NULL;                  // new node will be the last node
    node->prev = NULL;                  // clear prev before connecting

    if (*list == NULL) {                // check if list is empty
        *list = node;                   // new node becomes head
        return;
    }

    current = *list;                    // start at the head

    while (current->next != NULL) {     // loop until current is last node
        current = current->next;        // move to next node
    }

    current->next = node;               // old last node points to new node
    node->prev = current;               // new node points back to old last node
}


/*
    Get the n-th node.
    n starts at 1.
*/
dNode *getDNthNode(dNode *list, int n) {
    int count;                          // current position number
    dNode *current;                     // pointer used to walk through list

    if (n <= 0) {                       // 0 or negative is invalid
        return NULL;
    }

    count = 1;                          // first node is position 1
    current = list;                     // start at head

    while (current != NULL) {           // loop through list
        if (count == n) {               // check if this is the n-th node
            return current;             // return the node
        }

        current = current->next;        // move to next node
        count++;                        // increase position count
    }

    return NULL;                        // n was too large
}


/*
    Detach a node from the list, but do not free it.
    This is used for get because get moves the node to the front.

    In a doubly linked list, I must fix both:
        previous node's next pointer
        next node's prev pointer
*/
dNode *detachDNode(dNode **list, dNode *target) {
    dNode *current;                     // node I am checking

    if (list == NULL || *list == NULL || target == NULL) {
        return NULL;                    // check bad arguments
    }

    current = *list;                    // start at head

    while (current != NULL) {           // loop through list
        if (current == target) {        // check if current is target

            if (current->prev != NULL) { // check if current has previous node
                current->prev->next = current->next; // previous node skips current
            }
            else {                      // current is the head
                *list = current->next;  // move head to next node
            }

            if (current->next != NULL) { // check if current has next node
                current->next->prev = current->prev; // next node points back correctly
            }

            current->next = NULL;       // disconnect current from next node
            current->prev = NULL;       // disconnect current from previous node

            return current;             // return detached node
        }

        current = current->next;        // move to next node
    }

    return NULL;                        // target was not found
}


/*
    Delete a node from the list.
*/
void deleteDNode(dNode **list, dNode *target) {
    dNode *removed;                     // detached node

    removed = detachDNode(list, target); // remove node from list

    if (removed == NULL) {              // check if node was not found
        return;
    }

    freeCity((city *)removed->data);    // free city inside node
    free(removed);                      // free node
}


/*
    Count the number of nodes in the list.
*/
int getDListLength(dNode *list) {
    int count;                          // number of nodes
    dNode *current;                     // pointer used to walk through list

    count = 0;                          // start count at 0
    current = list;                     // start at head

    while (current != NULL) {           // loop until end of list
        count++;                        // count this node
        current = current->next;        // move to next node
    }

    return count;                       // return list size
}


/*
    Reverse the doubly linked list.
    For each node, I swap next and prev.
*/
void reverseDList(dNode **list) {
    dNode *current;                     // node being changed
    dNode *nextNode;                    // saves old next node
    dNode *newHead;                     // new head after reversing

    if (list == NULL) {                 // check bad argument
        return;
    }

    current = *list;                    // start at old head
    newHead = NULL;                     // new head starts as NULL

    while (current != NULL) {           // loop through list
        nextNode = current->next;       // save old next node first
        current->next = current->prev;  // next becomes old prev
        current->prev = nextNode;       // prev becomes old next
        newHead = current;              // last visited node becomes new head
        current = nextNode;             // move to old next node
    }

    *list = newHead;                    // update list head
}


/*
    Print the first n cities in the list.
*/
void printFirstDCities(dNode *list, int n) {
    int count;                          // number printed
    dNode *current;                     // pointer used to walk through list

    if (n <= 0) {                       // check bad number
        return;
    }

    count = 0;                          // start printed count at 0
    current = list;                     // start at head

    while (current != NULL && count < n) { // stop at end or after n cities
        printCity((city *)current->data);  // print city in this node
        current = current->next;        // move to next node
        count++;                        // increase printed count
    }
}


/*
    Free the whole doubly linked list.
*/
void freeDList(dNode *list) {
    dNode *current;                     // current node
    dNode *nextNode;                    // saves next node

    current = list;                     // start at head

    while (current != NULL) {           // loop through whole list
        nextNode = current->next;       // save next before freeing current
        freeCity((city *)current->data); // free city data
        free(current);                  // free node
        current = nextNode;             // move to saved next node
    }
}


/*
    Read the first 20 cities into a doubly linked list.
*/
dNode *readCityList(char *filename) {
    FILE *fp;                           // file pointer
    char line[10000];                   // one line from file
    int i;                              // loop counter
    city *c;                            // city pointer
    dNode *node;                        // node pointer
    dNode *list;                        // head of linked list

    list = NULL;                        // start with empty list

    fp = fopen(filename, "r");          // open CSV file

    if (fp == NULL) {                   // check if file opened
        printf("Could not open file: %s\n", filename);
        exit(1);
    }

    if (fgets(line, 10000, fp) == NULL) { // read header line
        printf("Could not read header line.\n");
        fclose(fp);
        exit(1);
    }

    for (i = 0; i < 20; i++) {          // read first 20 city lines
        if (fgets(line, 10000, fp) == NULL) { // read one city line
            printf("Could not read city line %d.\n", i + 1);
            fclose(fp);
            exit(1);
        }

        c = stringToCity(line);         // convert line to city struct
        node = createDNode(c);          // put city into a node
        addDNodeEnd(&list, node);       // add node to end of list
    }

    fclose(fp);                         // close file

    return list;                        // return head of list
}


/*
    Main command loop.
*/
int main(void) {
    dNode *list;                        // head of linked list
    dNode *node;                        // node used for delete/get
    char s[100];                        // user input string
    int n;                              // user number

    list = readCityList("uscities.csv"); // read first 20 cities

    while (1) {                         // keep asking commands
        printf("size, delete, reverse, get, or print: ");

        if (fgets(s, 100, stdin) == NULL) { // read command
            break;                      // stop if input fails
        }

        killNewline(s);                 // remove newline from command

        if (strcmp(s, "size") == 0) {   // size command
            printf("Size is %d\n", getDListLength(list));
        }
        else if (strcmp(s, "delete") == 0) { // delete command
            printf("Enter a number: ");

            if (fgets(s, 100, stdin) == NULL) { // read number
                break;
            }

            n = atoi(s);                // convert input to int
            node = getDNthNode(list, n); // find n-th node

            if (node == NULL) {         // check bad number
                printf("Invalid number\n");
            }
            else {
                deleteDNode(&list, node); // delete n-th node
            }
        }
        else if (strcmp(s, "reverse") == 0) { // reverse command
            reverseDList(&list);        // reverse list
        }
        else if (strcmp(s, "get") == 0) { // get command
            printf("Enter a number: ");

            if (fgets(s, 100, stdin) == NULL) { // read number
                break;
            }

            n = atoi(s);                // convert input to int
            node = getDNthNode(list, n); // find n-th node

            if (node == NULL) {         // check bad number
                printf("Invalid number\n");
            }
            else {
                node = detachDNode(&list, node); // remove node but keep it
                addDNodeFront(&list, node);      // move node to front
            }
        }
        else if (strcmp(s, "print") == 0) { // print command
            printf("Enter a number: ");

            if (fgets(s, 100, stdin) == NULL) { // read number
                break;
            }

            n = atoi(s);                // convert input to int
            printFirstDCities(list, n); // print first n cities
        }
        else {
            break;                      // any other command stops program
        }
    }

    freeDList(list);                    // free all remaining nodes and cities

    return 0;                           // end program
}
