#include <stdio.h>                              // use printf and fgets
#include <stdlib.h>                             // use malloc
#include <string.h>                             // use strcpy, strcat, strncmp

typedef struct zooNode {                        // define one tree node
    int isAnimal;                               // 1 means animal node, 0 means question node
    char animalName[100];                       // store animal name
    char questionText[200];                     // store question text
    struct zooNode *noChild;                    // child for no answer
    struct zooNode *yesChild;                   // child for yes answer
} zooNode;                                      // give the struct a short name

zooNode *topNode = NULL;                        // root of the whole zoo tree

void removeNewline(char s[]) {                  // remove newline from fgets
    int i = 0;                                  // start at first character

    while (s[i] != '\0') {                      // loop until the end of string
        if (s[i] == '\n') {                     // check if current character is newline
            s[i] = '\0';                        // change newline to end of string
            return;                             // leave the function
        }
        i++;                                    // move to next character
    }
}

int isYes(char s[]) {                           // check if user says yes
    if (s[0] == 'y' || s[0] == 'Y') {           // accept yes, Yes, y, Y
        return 1;                               // return true
    }

    return 0;                                   // otherwise return false
}

int isNo(char s[]) {                            // check if user says no
    if (s[0] == 'n' || s[0] == 'N') {           // accept no, No, n, N
        return 1;                               // return true
    }

    return 0;                                   // otherwise return false
}

zooNode *createAnimalNode(char *animalName) {   // create one animal node
    zooNode *newNode;                           // make a pointer for new node

    newNode = malloc(sizeof(zooNode));          // allocate memory for one zooNode

    if (newNode == NULL) {                      // check if malloc failed
        printf("Memory error.\n");              // print error message
        return NULL;                            // return NULL if failed
    }

    newNode->isAnimal = 1;                      // mark this node as animal node
    strcpy(newNode->animalName, animalName);    // copy animal name into node
    newNode->questionText[0] = '\0';            // animal node does not need question text
    newNode->noChild = NULL;                    // animal node has no no child
    newNode->yesChild = NULL;                   // animal node has no yes child

    return newNode;                             // return the new animal node
}

zooNode *createQuestionNode(char *questionText, zooNode *noAnimal, zooNode *yesAnimal) {   // create one question node
    zooNode *newNode;                           // make a pointer for new node

    newNode = malloc(sizeof(zooNode));          // allocate memory for one zooNode

    if (newNode == NULL) {                      // check if malloc failed
        printf("Memory error.\n");              // print error message
        return NULL;                            // return NULL if failed
    }

    newNode->isAnimal = 0;                      // mark this node as question node
    newNode->animalName[0] = '\0';              // question node does not need animal name
    strcpy(newNode->questionText, questionText);// copy question text into node
    newNode->noChild = noAnimal;                // no child is the old animal
    newNode->yesChild = yesAnimal;              // yes child is the new animal

    return newNode;                             // return the new question node
}

void interact(zooNode *node, zooNode *parent, int yesLink) {   // interact with current node
    char s[100];                                               // store yes or no answer

    if (node == NULL) {                                        // safety check
        return;                                                // stop if node is NULL
    }

    if (node->isAnimal == 0) {                                 // check if this is a question node
        printf("%s ", node->questionText);                     // print the question
        fgets(s, 100, stdin);                                  // read user answer
        removeNewline(s);                                      // remove newline

        if (isYes(s)) {                                        // if answer is yes
            interact(node->yesChild, node, 1);                 // go to yes child
        }
        else if (isNo(s)) {                                    // if answer is no
            interact(node->noChild, node, 0);                  // go to no child
        }
        else {                                                 // if answer is not yes or no
            printf("Please answer yes or no.\n");              // print warning
        }

        return;                                                // finish question node
    }

    printf("Is it a %s? ", node->animalName);                  // guess the animal
    fgets(s, 100, stdin);                                      // read user answer
    removeNewline(s);                                          // remove newline

    if (isYes(s)) {                                            // if the guess is right
        printf("I guessed your animal!\n");                    // print success message
        return;                                                // finish this round
    }

    if (isNo(s)) {                                             // if the guess is wrong
        char newAnimal[100];                                   // store new animal name
        char difference[100];                                  // store difference sentence
        char question[200];                                    // store new question
        zooNode *newAnimalNode;                                // pointer to new animal node
        zooNode *newQuestionNode;                              // pointer to new question node

        printf("What is your animal called? ");                // ask for new animal
        fgets(newAnimal, 100, stdin);                          // read new animal name
        removeNewline(newAnimal);                              // remove newline

        printf("How would you tell a %s from a %s?\n", newAnimal, node->animalName);   // ask difference
        printf("A %s has or is: ", newAnimal);                 // ask user to start with has or is
        fgets(difference, 100, stdin);                         // read difference
        removeNewline(difference);                             // remove newline

        if (strncmp(difference, "is ", 3) == 0) {              // check if difference starts with is
            strcpy(question, "Is it ");                        // start question with Is it
            strcat(question, difference + 3);                  // add words after is
            strcat(question, "?");                             // add question mark
        }
        else if (strncmp(difference, "has ", 4) == 0) {        // check if difference starts with has
            strcpy(question, "Does it have ");                 // start question with Does it have
            strcat(question, difference + 4);                  // add words after has
            strcat(question, "?");                             // add question mark
        }
        else {                                                 // if input does not start with is or has
            printf("Please start with 'is ' or 'has '.\n");    // print error message
            return;                                            // do not add new animal
        }

        newAnimalNode = createAnimalNode(newAnimal);           // create new animal node

        if (newAnimalNode == NULL) {                           // check if animal node failed
            return;                                            // stop if failed
        }

        newQuestionNode = createQuestionNode(question, node, newAnimalNode);   // create new question node

        if (newQuestionNode == NULL) {                         // check if question node failed
            return;                                            // stop if failed
        }

        if (parent == NULL) {                                  // if current node is the root
            topNode = newQuestionNode;                         // replace root with new question
        }
        else if (yesLink) {                                    // if current node is parent's yes child
            parent->yesChild = newQuestionNode;                // replace parent's yes child
        }
        else {                                                 // otherwise current node is parent's no child
            parent->noChild = newQuestionNode;                 // replace parent's no child
        }

        printf("Thanks for telling me about the %s.\n", newAnimal);   // print thank you
        return;                                                      // finish this round
    }

    printf("Please answer yes or no.\n");                      // if user did not answer yes or no
}

int main() {                                                    // main function
    char s[100];                                                // store play again answer

    topNode = createAnimalNode("Lion");                        // start tree with Lion

    if (topNode == NULL) {                                      // check if Lion node was created
        return 1;                                               // stop program if failed
    }

    while (1) {                                                 // keep playing
        printf("\nThink of an animal.\n");                      // tell user to think of animal
        interact(topNode, NULL, 0);                             // start from root of tree

        printf("\nDo you want to play again? ");                // ask if user wants another round
        fgets(s, 100, stdin);                                   // read answer
        removeNewline(s);                                       // remove newline

        if (isNo(s)) {                                          // if user says no
            printf("Goodbye!\n");                               // print goodbye
            break;                                              // stop loop
        }
    }

    return 0;                                                   // program ends successfully
}
