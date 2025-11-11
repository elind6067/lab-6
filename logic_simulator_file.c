#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gates.h"

/*
    Ella Lind
    ECE 321L - 001
    Lab 9 - Logic Gate Simulator Part 5
    11/10/2025
    Description: This program simulates a circuit given a file with the circuit description and user inputs. 
    The first line of the file represents n gates, including user inputs and output, and each subsequent 
    line represents the order and operation of the gates.
    Uses a double linked list to store the circuit elements read from the file.
    Updated to handle mutiple inputs for AND and OR gates, using AND_N and OR_N functions and an array of inputs.
*/

/*
    node structure from "8_adt_lists" slides
*/
typedef struct dlist_tag {
    int index;        // gate index
    char type;        // gate type 
    int *inputs;         // input indices array
    int nInputs;         // number of inputs
    int output;       // output
    struct dlist_tag *next;
    struct dlist_tag *prev;
} DListNode;
typedef struct {
    DListNode *first;
    DListNode *last;
} dl;


/*
    function prototypes
*/
void dlInit(dl *list);
void dlInsert(dl *lp, int index, char type, int *inputs, int nInputs, int output);
DListNode *dlFindNode(dl *lp, int index);
void dlPrint(dl lp); // for testing purposes
void dlFree(dl *lp);

// takes a file as command line argument
int main(int argc, char *argv[]) {
    /*
        file handling
    */
    FILE *file = fopen(argv[1], "r"); // open file as read only
    if (file == NULL) {
        printf("Error opening file: %s\n", argv[1]);
        return 1;
    }

    /*
        initialize circuit description
    */
    dl circuit;
    dlInit(&circuit);
    int nGates;
    if (fscanf(file, "%d", &nGates) != 1) {
        printf("Cannot read number of gates\n");
        fclose(file);
        return 1;
    }

    /*
        read circuit description from file
    */
    char line[256]; // char array for reading lines
    fgets(line, sizeof(line), file);

    int linesRead = 0;
    while (linesRead < nGates && fgets(line, sizeof(line), file) != NULL) {
        int gindex = 0;
        char gtype = '\0';
        int nonInputs = 0;
        // get the gate index and type, and the number of characters that are not inputs
        if (sscanf(line, " %d %c %n", &gindex, &gtype, &nonInputs) < 2) {
            // skip empty line
            continue;
        }

        int temp[64]; // empty array for input indicies, can handle 64 inputs
        int nInputs = 0;
        char *p = line + nonInputs; // line address + the offset from the gate index and type
        int added = 0;
        int inputValue = 0;
        while (sscanf(p, " %d %n", &inputValue, &added) == 1) {
            if (nInputs < 64){
                temp[nInputs++] = inputValue; // add the input value to the next address in temp
            }
            p += added; // also move pointer to the next input by the size of an integer
        }

        int *inPointer = NULL; // new array for inputs
        if (nInputs > 0) {
            inPointer = malloc(nInputs * sizeof(int));
            if (!inPointer) {
                printf("Memory allocation failed\n");
                dlFree(&circuit);
                fclose(file);
                return 1;
            }
            for (int k = 0; k < nInputs; k++) {
                inPointer[k] = temp[k]; // put the temp values into the input array
            } 
        }

        dlInsert(&circuit, gindex, gtype, inPointer, nInputs, -1);
        linesRead++;
    }

    /*
       get user inputs and evaluate circuit
    */ 
    DListNode *current;
    current = circuit.first; // start with first node of circuit
    while (current != NULL) {
        if (current->type == 'I') { // user input gates
            // prompt for input value and store in node
            int value = -1;
            int read = 1;
            while (read) {
                printf("Enter value for input gate %d (0 or 1): ", current->index);
                if (scanf("%d", &value) != read) {
                    int c;
                    while ((c = getchar()) != '\n' && c != EOF) { // error handling 
                        printf("Please enter 0 or 1\n");
                        continue;
                    }
                    linesRead++;
                }
                if (value == 0 || value == 1) {
                    break;
                }
                printf("Please enter 0 or 1\n");
            }
            current->output = value; // output is user input value
            current = current->next; // move to next node
            continue;
        }
        if (current->type != 'I') { // non input gates
            int out = 0;
            if (current->type == 'N') {
                int input = 0;
                if (current->nInputs > 0) {
                    DListNode *n1 = dlFindNode(&circuit, current->inputs[0]);
                    if (n1 != NULL) {
                        input = n1->output; // only need 1 input
                    } 
                    else {
                        input = 0;
                    }
                }
                out = NOT(input);
            } 
            else if (current->type == 'A') {
                int *inputs = NULL; // new local inputs array for gate type
                if (current->nInputs > 0) {
                    inputs = malloc(current->nInputs * sizeof(int));
                    if (!inputs) {
                        printf("Memory allocation failed\n"); 
                        dlFree(&circuit); 
                        fclose(file); 
                        return 1; 
                    }
                    for (int k = 0; k < current->nInputs; k++) {
                        DListNode *n = dlFindNode(&circuit, current->inputs[k]);
                        if (n != NULL) {
                            inputs[k] = n->output; // output of gate at specified index k becomes input for the AND_N gate
                        }
                        else {
                            inputs[k] = 0; // otherwise default to 0 because anything AND 0 is 0
                        }
                    }
                }
                out = AND_N(inputs, current->nInputs);
                free(inputs); // free memory
            } 
            else if (current->type == 'O') {
                int *inputs = NULL;
                if (current->nInputs > 0) {
                    inputs = malloc(current->nInputs * sizeof(int));
                    if (!inputs) { 
                        printf("Memory allocation failed\n"); 
                        dlFree(&circuit); 
                        fclose(file); 
                        return 1; 
                    }
                    for (int k = 0; k < current->nInputs; k++) {
                        DListNode *n = dlFindNode(&circuit, current->inputs[k]);
                        if (n != NULL) {
                            inputs[k] = n->output;
                        }
                        else {
                            inputs[k] = 0;
                        }
                    }
                }
                if (current->nInputs > 0) {
                    out = OR_N(inputs, current->nInputs);
                } 
                else {
                    out = OR_N(NULL, 0); // handle 0 inputs case
                }
                free(inputs);
            }
            else if (current->type == 'X') {
                int value = 0;
                int input = 0;
                for (int k = 0; k < current->nInputs; k++) {
                    DListNode *n = dlFindNode(&circuit, current->inputs[k]);
                    if (n != NULL) {
                        input = n->output;
                    }
                    else {
                        input = 0;
                    }
                    value = XOR(value, input); // XOR old input with new input
                }
                out = value;
            } 
            else if (current->type == 'Q') {
                int input = 0;
                if (current->nInputs > 0) {
                    DListNode *n1 = dlFindNode(&circuit, current->inputs[0]);
                    if (n1 != NULL) {
                        input = n1->output;
                    }
                    else {
                        input = 0;
                    }
                }
                out = BUFFER(input);
            } 
            else {
                printf("Unknown gate type");
                out = 0;
            }
            current->output = out; // otherwise output for non input gate is 0
        }
        current = current->next; // move to next node
    }

    // print results from the linked list for testing purposes
    printf("Gate outputs:\n");
    dlPrint(circuit);

    // final output is output of last node
    if (circuit.last != NULL) {
        printf("Final output (gate %d) = %d\n", circuit.last->index, circuit.last->output);
    }
    // clear linked list
    dlFree(&circuit);
    fclose(file);
    return 0;
}

/*
    functions
*/
void dlPrint(dl lp) {
    DListNode *current = lp.first;
    while (current != NULL) {
        printf("%d: %d\n", current->index, current->output);
        current = current->next;
    }
}

void dlFree(dl *lp) {
    DListNode *current = lp->first;
    while (current != NULL) { // clears the whole list
        DListNode *next = current->next;
        if (current->inputs != NULL) free(current->inputs);
        free(current);
        current = next;
    }
    lp->first = lp->last = NULL;
}

void dlInit(dl *list) {
    list->first = NULL;
    list->last = NULL;
}
void dlInsert(dl *lp, int index, char type, int *inputs, int nInputs, int output) {
    DListNode *node = (DListNode *)malloc(sizeof(DListNode));
    if (!node) {
        if (inputs) free(inputs);
        return; // allocation failed
    }
    // initialize
    node->index = index;
    node->type = type;
    node->inputs = inputs;
    node->nInputs = nInputs;
    node->output = output;
    node->next = NULL; 
    node->prev = NULL;
    if (lp->last == NULL) {
        lp->first = node;
        lp->last = node;
    } else {
        lp->last->next = node; // new node after last
        node->prev = lp->last; // connect prev to new node
        lp->last = node; // move last pointer to new node
    }
}
// return node by gate index
DListNode *dlFindNode(dl *lp, int index) {
    DListNode *current = lp->first; 
    while (current != NULL) {
        if (current->index == index) 
            return current;
        current = current->next; // traverse list from first to last until index matches given index
    }
    return NULL; // if node does not exist
}