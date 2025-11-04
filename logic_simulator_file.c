#include <stdio.h>
#include <stdlib.h>
#include "gates.h"

/*
    Ella Lind
    ECE 321L - 001
    Lab 6 - Logic Gate Simulator Part 4
    11/03/2025
    Description: This program simulates a circuit given a file with the circuit description and user inputs. 
    The first line of the file represents n gates, including user inputs and output, and each subsequent 
    line represents the order and operation of the gates.
    Uses a double linked list to store the circuit elements read from the file.
*/

/*
    node structure from "8_adt_lists" slides
*/
typedef struct dlist_tag {
    int index;        // gate index
    char type;        // gate type character
    int in1;          // input 1 
    int in2;          // input 2 
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
void dlInsert(dl *lp, int index, char type, int in1, int in2, int output);
DListNode *dlFindNode(dl *lp, int index);
void dlPrint(dl lp); // for testing purposes
void dlFree(dl *lp);

// takes a file as command line argument
int main(int argc, char *argv[]) {
    /*
        file handling
    */
    if (argc != 2) {
        printf("Usage: %s <circuit_file>\n", argv[0]);
        return 1;
    }
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
    char line[256]; // char array (string) for reading lines
    fgets(line, sizeof(line), file);

    int linesRead = 0;
    while (!feof(file) && linesRead < nGates) {
        if (fgets(line, sizeof(line), file) == NULL) 
            break;
        linesRead++;
        int idx = 0, in1 = 0, in2 = 0;
        char gtype = '\0'; // return char, separated by spaces
        if (sscanf(line, "%d: %c %d %d", &idx, &gtype, &in1, &in2) < 2) {
            continue;
        }

    // insert gates into linked list with output = -1 (temporary)
        dlInsert(&circuit, idx, gtype, in1, in2, -1);
    }

    /*
       get user inputs and evaluate circuit
    */ 
    DListNode *current;
    current = circuit.first; // start with first node of circuit
    while (current != NULL) {
        if (current->type == 'I') { // user input gates
            // prompt for input value and store in node
            int val = -1;
            int read = 1;
            while (read) {
                printf("Enter value for input gate %d (0 or 1): ", current->index);
                if (scanf("%d", &val) != read) {
                    int c;
                    while ((c = getchar()) != '\n' && c != EOF) { // error handling 
                        printf("Please enter 0 or 1.\n");
                        continue;
                    }       
                }
                if (val == 0 || val == 1) break;
                printf("Please enter 0 or 1.\n");
            }
            current->output = val; // output is user input value
            current = current->next; // move to next node
            continue;
        }
        if (current->type != 'I') { // non input gates
            int val1 = 0, val2 = 0; // temporary variables to hold old input values
            DListNode *n1 = NULL; // temporary pointers for current->in1, in2
            DListNode *n2 = NULL;
            switch (current->type) {
                case 'N':
                    n1 = dlFindNode(&circuit, current->in1); // temp pointer assigned to node returned by dlFindNode (if in1 matches)
                    if (n1 != NULL) {
                            val1 = n1->output; // current->output stored in val
                        } 
                    else {
                            val1 = 0; // only has one input 'gate', default 0
                        }
                    current->output = NOT(val1); // result of gate operation replaces old current->output (n1->output)
                    break;
                case 'A':
                    n1 = dlFindNode(&circuit, current->in1);
                    n2 = dlFindNode(&circuit, current->in2);
                    if (n1 != NULL) {
                        val1 = n1->output;
                    } 
                    else {
                        val1 = 0;
                    }
                    if (n2 != NULL) {
                        val2 = n2->output;
                    } 
                    else {
                        val2 = 0;
                    }
                    current->output = AND(val1, val2);
                    break;
                case 'O':
                    n1 = dlFindNode(&circuit, current->in1);
                    n2 = dlFindNode(&circuit, current->in2);
                    if (n1 != NULL) {
                        val1 = n1->output;
                    } 
                    else {
                        val1 = 0;
                    }
                    if (n2 != NULL) {
                        val2 = n2->output;
                    } 
                    else {
                        val2 = 0;
                    }
                    current->output = OR(val1, val2);
                    break;
                case 'X':
                    n1 = dlFindNode(&circuit, current->in1);
                    n2 = dlFindNode(&circuit, current->in2);
                    if (n1 != NULL) {
                        val1 = n1->output;
                    } 
                    else {
                        val1 = 0;
                    }
                    if (n2 != NULL) {
                        val2 = n2->output;
                    } 
                    else {
                        val2 = 0;
                    }
                    current->output = XOR(val1, val2);
                    break;
                case 'Q':
                    n1 = dlFindNode(&circuit, current->in1);
                    if (n1 != NULL) {
                        val1 = n1->output;
                    } 
                    else {
                        val1 = 0;
                    }
                    current->output = BUFFER(val1); // use buffer gate for output, does not change
                    break;
                default: // error handling for unknown gate types
                    printf("Unknown gate type '%c' at index %d\n", current->type, current->index);
                    current->output = 0;
                    break;
            }
        }
        current = current->next; // move to next node
    }

    // print results from the linked list
    printf("Gate outputs:\n");
    dlPrint(circuit);

    // final output is output of last node
    if (circuit.last != NULL) {
        printf("Final output (gate %d) = %d\n", circuit.last->index, circuit.last->output);
    }
    // clean up linked list
    dlFree(&circuit);
    fclose(file);
    return 0;
}

// functions
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
        free(current);
        current = next;
    }
    lp->first = lp->last = NULL;
}

void dlInit(dl *list) {
    list->first = NULL;
    list->last = NULL;
}
void dlInsert(dl *lp, int index, char type, int in1, int in2, int output) {
    DListNode *node = (DListNode *)malloc(sizeof(DListNode));
    if (!node) return; // empty list
    node->index = index;
    node->type = type;
    node->in1 = in1;
    node->in2 = in2;
    node->output = output;
    node->next = NULL; // initialize
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