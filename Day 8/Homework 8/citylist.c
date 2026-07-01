#include <stdio.h>                                      // use printf, fgets, FILE
#include <stdlib.h>                                     // use malloc, free, atoi, atof
#include <string.h>                                     // use strcmp, strcpy, strncpy

#define MAX_LINE 10000                                  // big buffer for one csv line
#define MAX_FIELD 300                                   // buffer for one csv field

typedef struct city {                                   // define city data
    char name[100];                                     // city name
    char state[10];                                     // state abbreviation
    int countyFips;                                     // county FIPS code
    double lat;                                         // latitude
    double lng;                                         // longitude
    int population;                                     // population
} city;                                                 // short name for struct city

typedef struct vector {                                 // define generic vector
    void **data;                                        // array of void pointers
    int size;                                           // number of used spaces
    int capacity;                                       // total spaces available
} vector;                                               // short name for struct vector

typedef struct treeNode {                               // define BST node
    city *cityData;                                     // pointer to city struct
    struct treeNode *left;                              // left child
    struct treeNode *right;                             // right child
} treeNode;                                             // short name for tree node

void removeNewline(char s[]) {                          // remove newline from fgets input
    int i = 0;                                          // start at index 0

    while (s[i] != '\0') {                              // loop until end of string
        if (s[i] == '\n') {                             // if newline is found
            s[i] = '\0';                                // replace newline with string end
            return;                                     // stop function
        }

        i++;                                            // move to next character
    }
}

vector *createVector(int capacity) {                    // create a new vector
    vector *v;                                          // pointer to vector

    v = malloc(sizeof(vector));                         // allocate memory for vector

    if (v == NULL) {                                    // check malloc failure
        printf("Memory error.\n");                      // print error message
        return NULL;                                    // return NULL
    }

    if (capacity < 1) {                                 // check bad capacity
        capacity = 10;                                  // use default capacity
    }

    v->data = malloc(capacity * sizeof(void *));         // allocate array of void pointers

    if (v->data == NULL) {                              // check malloc failure
        printf("Memory error.\n");                      // print error message
        free(v);                                        // free vector struct
        return NULL;                                    // return NULL
    }

    v->size = 0;                                        // vector starts empty
    v->capacity = capacity;                             // save capacity

    return v;                                           // return new vector
}

int vectorAdd(vector *v, void *item) {                  // add one item to vector
    int i;                                              // loop variable
    void **newData;                                     // new bigger array

    if (v == NULL) {                                    // check vector pointer
        return 0;                                       // return failure
    }

    if (v->size >= v->capacity) {                       // if vector is full
        newData = malloc(v->capacity * 2 * sizeof(void *)); // allocate bigger array

        if (newData == NULL) {                          // check malloc failure
            printf("Memory error.\n");                  // print error message
            return 0;                                   // return failure
        }

        for (i = 0; i < v->size; i++) {                 // copy old items
            newData[i] = v->data[i];                    // copy one pointer
        }

        free(v->data);                                  // free old array
        v->data = newData;                              // use new array
        v->capacity = v->capacity * 2;                  // update capacity
    }

    v->data[v->size] = item;                            // put item at end
    v->size++;                                          // increase size

    return 1;                                           // return success
}

void *vectorGet(vector *v, int index) {                 // get item from vector
    if (v == NULL) {                                    // check vector pointer
        return NULL;                                    // return NULL
    }

    if (index < 0 || index >= v->size) {                // check index range
        return NULL;                                    // return NULL
    }

    return v->data[index];                              // return item pointer
}

void getNextField(char line[], int *pos, char field[]) { // read one csv field
    int j = 0;                                          // index for field

    if (line[*pos] == '"') {                            // check if field starts with quote
        (*pos)++;                                       // skip first quote

        while (line[*pos] != '\0') {                    // loop through quoted field
            if (line[*pos] == '"' && line[*pos + 1] == '"') { // check double quote
                if (j < MAX_FIELD - 1) {                // make sure field has space
                    field[j] = '"';                     // copy one quote
                    j++;                                // move field index
                }

                *pos = *pos + 2;                        // skip two quote characters
            }
            else if (line[*pos] == '"') {               // check ending quote
                (*pos)++;                               // skip ending quote
                break;                                  // stop quoted field
            }
            else {                                      // normal character
                if (j < MAX_FIELD - 1) {                // make sure field has space
                    field[j] = line[*pos];              // copy character
                    j++;                                // move field index
                }

                (*pos)++;                               // move line index
            }
        }

        field[j] = '\0';                                // end field string

        if (line[*pos] == ',') {                        // if next character is comma
            (*pos)++;                                   // skip comma
        }

        return;                                         // finish function
    }

    while (line[*pos] != '\0' && line[*pos] != ',' && line[*pos] != '\n' && line[*pos] != '\r') { // normal field
        if (j < MAX_FIELD - 1) {                        // make sure field has space
            field[j] = line[*pos];                      // copy character
            j++;                                        // move field index
        }

        (*pos)++;                                       // move line index
    }

    field[j] = '\0';                                    // end field string

    if (line[*pos] == ',') {                            // if current character is comma
        (*pos)++;                                       // skip comma
    }
}

city *createCityFromLine(char line[]) {                 // make city from csv line
    city *c;                                            // city pointer
    char field[MAX_FIELD];                              // one csv field
    int pos = 0;                                        // current position in line
    int column = 1;                                     // current column number

    c = malloc(sizeof(city));                           // allocate one city struct

    if (c == NULL) {                                    // check malloc failure
        printf("Memory error.\n");                      // print error message
        return NULL;                                    // return NULL
    }

    c->name[0] = '\0';                                  // start name empty
    c->state[0] = '\0';                                 // start state empty
    c->countyFips = 0;                                  // start FIPS as 0
    c->lat = 0.0;                                       // start latitude as 0
    c->lng = 0.0;                                       // start longitude as 0
    c->population = 0;                                  // start population as 0

    while (column <= 9) {                               // only need first 9 columns
        getNextField(line, &pos, field);                // read next field

        if (column == 2) {                              // column 2 is city name
            strncpy(c->name, field, 99);                // copy city name
            c->name[99] = '\0';                         // make sure string ends
        }
        else if (column == 3) {                         // column 3 is state
            strncpy(c->state, field, 9);                // copy state
            c->state[9] = '\0';                         // make sure string ends
        }
        else if (column == 5) {                         // column 5 is county FIPS
            c->countyFips = atoi(field);                // convert FIPS to int
        }
        else if (column == 7) {                         // column 7 is latitude
            c->lat = atof(field);                       // convert latitude to double
        }
        else if (column == 8) {                         // column 8 is longitude
            c->lng = atof(field);                       // convert longitude to double
        }
        else if (column == 9) {                         // column 9 is population
            c->population = atoi(field);                // convert population to int
        }

        column++;                                       // move to next column
    }

    return c;                                           // return city pointer
}

void printCity(city *c) {                               // print one city
    if (c == NULL) {                                    // check city pointer
        return;                                         // stop if NULL
    }

    printf("%s %s, population %d, at (%.4f, %.4f)\n", c->name, c->state, c->population, c->lat, c->lng); // print city
}

treeNode *createTreeNode(city *c) {                     // create one tree node
    treeNode *node;                                     // tree node pointer

    node = malloc(sizeof(treeNode));                    // allocate memory for tree node

    if (node == NULL) {                                 // check malloc failure
        printf("Memory error.\n");                      // print error message
        return NULL;                                    // return NULL
    }

    node->cityData = c;                                 // store city pointer
    node->left = NULL;                                  // left child starts NULL
    node->right = NULL;                                 // right child starts NULL

    return node;                                        // return tree node
}

treeNode *insertByLatitude(treeNode *root, city *c) {   // insert city ordered by latitude
    if (root == NULL) {                                 // if tree is empty here
        return createTreeNode(c);                       // create new node
    }

    if (c->lat < root->cityData->lat) {                 // smaller latitude goes left
        root->left = insertByLatitude(root->left, c);   // insert into left subtree
    }
    else {                                              // larger or equal latitude goes right
        root->right = insertByLatitude(root->right, c); // insert into right subtree
    }

    return root;                                        // return root
}

treeNode *insertByFips(treeNode *root, city *c) {       // insert city ordered by FIPS
    if (root == NULL) {                                 // if tree is empty here
        return createTreeNode(c);                       // create new node
    }

    if (c->countyFips < root->cityData->countyFips) {   // smaller FIPS goes left
        root->left = insertByFips(root->left, c);       // insert into left subtree
    }
    else if (c->countyFips > root->cityData->countyFips) { // larger FIPS goes right
        root->right = insertByFips(root->right, c);     // insert into right subtree
    }
    else {                                              // same FIPS already exists
        return root;                                    // ignore duplicate FIPS
    }

    return root;                                        // return root
}

int countTree(treeNode *root) {                         // count nodes in tree
    if (root == NULL) {                                 // empty tree
        return 0;                                       // zero nodes
    }

    return 1 + countTree(root->left) + countTree(root->right); // count root, left, right
}

void inorderToArray(treeNode *root, city *array[], int *index) { // put tree into array in sorted order
    if (root == NULL) {                                 // empty subtree
        return;                                         // stop
    }

    inorderToArray(root->left, array, index);            // visit left side first

    array[*index] = root->cityData;                      // put current city into array
    (*index)++;                                          // move to next array index

    inorderToArray(root->right, array, index);           // visit right side last
}

int linearSearchNewYork(city *array[], int n) {          // search New York one by one
    int i;                                               // loop variable

    for (i = 0; i < n; i++) {                            // check each city
        if (strcmp(array[i]->name, "New York") == 0) {   // compare city name
            return i;                                    // return index
        }
    }

    return -1;                                           // return -1 if not found
}

int binarySearchFips(city *array[], int n, int target) { // binary search by FIPS
    int low = 0;                                         // start index
    int high = n - 1;                                    // end index
    int mid;                                             // middle index

    while (low <= high) {                                // keep searching while valid
        mid = (low + high) / 2;                          // calculate middle index

        if (array[mid]->countyFips == target) {          // if target is found
            return mid;                                  // return index
        }
        else if (array[mid]->countyFips < target) {      // if middle value is too small
            low = mid + 1;                               // search right half
        }
        else {                                           // if middle value is too large
            high = mid - 1;                              // search left half
        }
    }

    return -1;                                           // return -1 if not found
}

FILE *openCityFile() {                                   // open uscities.csv
    FILE *file;                                          // file pointer

    file = fopen("uscities.csv", "r");                   // try current folder

    if (file != NULL) {                                  // if file opened
        return file;                                     // return file
    }

    file = fopen("../Resources/uscities.csv", "r");      // try Resources folder

    if (file != NULL) {                                  // if file opened
        return file;                                     // return file
    }

    file = fopen("../../Resources/uscities.csv", "r");   // try another Resources path

    return file;                                         // return file or NULL
}

void freeTree(treeNode *root) {                          // free tree nodes
    if (root == NULL) {                                  // empty tree
        return;                                          // stop
    }

    freeTree(root->left);                                // free left subtree
    freeTree(root->right);                               // free right subtree
    free(root);                                          // free current node
}

void freeVectorAndCities(vector *v) {                     // free vector and city structs
    int i;                                                // loop variable

    if (v == NULL) {                                      // check vector pointer
        return;                                           // stop if NULL
    }

    for (i = 0; i < v->size; i++) {                       // loop through city pointers
        free(v->data[i]);                                 // free one city struct
    }

    free(v->data);                                        // free vector array
    free(v);                                              // free vector struct
}

int main() {                                              // main function
    char s[100];                                          // user input buffer
    char line[MAX_LINE];                                  // csv line buffer
    int howMany;                                          // number of cities to read
    int i;                                                // loop variable
    FILE *file;                                           // csv file pointer
    vector *cities;                                       // vector of city pointers
    city *c;                                              // one city pointer
    treeNode *latTree = NULL;                             // BST ordered by latitude
    treeNode *fipsTree = NULL;                            // BST ordered by FIPS
    city **latArray;                                      // array ordered by latitude
    city **fipsArray;                                     // array ordered by FIPS
    int latCount;                                         // number of latitude tree nodes
    int fipsCount;                                        // number of FIPS tree nodes
    int index;                                            // array index for inorder traversal
    int nyIndex;                                          // index of New York
    int fipsIndex;                                        // index of FIPS 36081

    printf("How many cities: ");                          // ask user for number
    fgets(s, 100, stdin);                                 // read user input
    removeNewline(s);                                     // remove newline
    howMany = atoi(s);                                    // convert input to int

    if (howMany <= 0) {                                   // check bad number
        printf("Please enter a positive number.\n");      // print error message
        return 1;                                         // stop program
    }

    file = openCityFile();                                // open csv file

    if (file == NULL) {                                   // check file
        printf("Could not open uscities.csv.\n");         // print error message
        return 1;                                         // stop program
    }

    cities = createVector(howMany);                       // create vector

    if (cities == NULL) {                                 // check vector
        fclose(file);                                     // close file
        return 1;                                         // stop program
    }

    fgets(line, MAX_LINE, file);                          // skip header line

    while (cities->size < howMany && fgets(line, MAX_LINE, file) != NULL) { // read city lines
        c = createCityFromLine(line);                     // create city from line

        if (c != NULL) {                                  // check city pointer
            vectorAdd(cities, c);                         // add city pointer to vector
        }
    }

    fclose(file);                                         // close csv file

    printf("\n");                                         // print blank line

    for (i = 0; i < cities->size; i++) {                  // loop through vector
        c = (city *)vectorGet(cities, i);                 // get city pointer
        printCity(c);                                     // print city
    }

    for (i = 0; i < cities->size; i++) {                  // loop through cities
        c = (city *)vectorGet(cities, i);                 // get city pointer
        latTree = insertByLatitude(latTree, c);           // insert into latitude tree
    }

    latCount = countTree(latTree);                        // count latitude tree
    latArray = malloc(latCount * sizeof(city *));         // allocate latitude array

    if (latArray == NULL) {                               // check malloc failure
        printf("Memory error.\n");                        // print error message
        freeTree(latTree);                                // free latitude tree
        freeVectorAndCities(cities);                      // free vector and cities
        return 1;                                         // stop program
    }

    index = 0;                                            // start index at 0
    inorderToArray(latTree, latArray, &index);            // fill array by latitude

    nyIndex = linearSearchNewYork(latArray, latCount);    // find New York

    if (nyIndex >= 0) {                                   // if New York was found
        printf("\nBy latitude, New York is index %d\n", nyIndex); // print New York index
    }
    else {                                                // if New York was not found
        printf("\nNew York was not found by latitude.\n"); // print not found message
    }

    for (i = 0; i < cities->size; i++) {                  // loop through cities
        c = (city *)vectorGet(cities, i);                 // get city pointer
        fipsTree = insertByFips(fipsTree, c);             // insert into FIPS tree
    }

    fipsCount = countTree(fipsTree);                      // count FIPS tree
    fipsArray = malloc(fipsCount * sizeof(city *));       // allocate FIPS array

    if (fipsArray == NULL) {                              // check malloc failure
        printf("Memory error.\n");                        // print error message
        free(latArray);                                   // free latitude array
        freeTree(latTree);                                // free latitude tree
        freeTree(fipsTree);                               // free FIPS tree
        freeVectorAndCities(cities);                      // free vector and cities
        return 1;                                         // stop program
    }

    index = 0;                                            // start index at 0
    inorderToArray(fipsTree, fipsArray, &index);          // fill array by FIPS

    fipsIndex = binarySearchFips(fipsArray, fipsCount, 36081); // search FIPS 36081

    if (fipsIndex >= 0) {                                 // if FIPS was found
        printf("By FIPS code, %s is index %d\n", fipsArray[fipsIndex]->name, fipsIndex); // print name and index
    }
    else {                                                // if FIPS was not found
        printf("FIPS code 36081 was not found.\n");       // print not found message
    }

    free(latArray);                                       // free latitude array
    free(fipsArray);                                      // free FIPS array
    freeTree(latTree);                                    // free latitude tree
    freeTree(fipsTree);                                   // free FIPS tree
    freeVectorAndCities(cities);                          // free vector and cities

    return 0;                                             // program finished successfully
}