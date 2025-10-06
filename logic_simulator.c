#include <stdio.h>
#include "gates.h"

/*
    function prototypes
*/
int isnValid(int a);
void printNOT();
void printAND();
void printNAND();
void printOR();
void printNOR();
void printXOR();
void printXNOR();

int main() {
    char loop = 'C';
    int in1, in2, result, gate;
    while(loop) {
        printf("Select a gate to simulate:\n");
        printf("Enter 0 for NOT, 1 for AND, 2 for NAND, 3 for OR, 4 for NOR, 5 for XOR, 6 for XNOR\n");
        scanf("%d", &gate);
        if(gate == 0) {
            printf("Enter input: ");
            scanf("%d", &in1);
            if (isnValid(in1)) {
                break;
            }
            else {
                result = NOT(in1);
                printf("NOT %d = %d\n", in1, result);
                printNOT();
            } 
        }
        else if(gate >= 1 && gate <= 6) {
            printf("Enter two inputs: ");
            scanf("%d\n %d\n", &in1, &in2);
            if (isnValid(in1) || isnValid(in2)) {
                break;
            }
            else {
                switch(gate) {
                    case 1:
                        result = AND(in1, in2);
                        printf("%d AND %d = %d\n", in1, in2, result);
                        printAND();
                        break;
                    case 2:
                        result = NAND(in1, in2);
                        printf("%d NAND %d = %d\n", in1, in2, result);
                        printNAND();
                        break;
                    case 3:
                        result = OR(in1, in2);
                        printf("%d OR %d = %d\n", in1, in2, result);
                        printOR();
                        break;
                    case 4:
                        result = NOR(in1, in2);
                        printf("%d NOR %d = %d\n", in1, in2, result);
                        printNOR();
                        break;
                    case 5:
                        result = XOR(in1, in2);
                        printf("%d XOR %d = %d\n", in1, in2, result);
                        printXOR();
                        break;
                    case 6:
                        result = XNOR(in1, in2);
                        printf("%d XNOR %d = %d\n", in1, in2, result);
                        printXNOR();
                        break;
                }
            }
        }
        else {
            printf("Invalid gate selection\n");
        }
        // ask user to continue
        printf("Type 'Q' to quit, or 'C' to simulate another gate: ");
        scanf("%c", &loop);
        if(loop == 'Q' || loop == 'q') { // check for lowercase entry
            break;
        }
        else {
            loop = 'C'; // reset loop variable in case of invalid entry
        }
    }
    return 0;
}

/*
    function definitions
*/
int isnValid(int a) {
    printf("Invalid input. Please enter 0 or 1\n");
    return (a != 0 || a != 1);
}
/*
    truth table print functions don't recalculate results for every input case,
    just print static tables to verify results
*/
void printNOT() {
    printf("NOT Truth Table\n");
    printf("A | OUTPUT\n");
    printf("----------\n");
    printf("0 |  1\n");
    printf("1 |  0\n");
}
void printAND() {
    printf("AND Truth Table\n");
    printf("A | B | OUTPUT\n");
    printf("----------------\n");
    printf("0 | 0 |  0\n");
    printf("0 | 1 |  0\n");
    printf("1 | 0 |  0\n");
    printf("1 | 1 |  1\n");
}
void printNAND() {
    printf("NAND Truth Table\n");
    printf("A | B | OUTPUT\n");
    printf("----------------\n");
    printf("0 | 0 |  1\n");
    printf("0 | 1 |  1\n");
    printf("1 | 0 |  1\n");
    printf("1 | 1 |  0\n");
}
void printOR() {
    printf("OR Truth Table\n");
    printf("A | B | OUTPUT\n");
    printf("----------------\n");
    printf("0 | 0 |  0\n");
    printf("0 | 1 |  1\n");
    printf("1 | 0 |  1\n");
    printf("1 | 1 |  1\n");
}
void printNOR() {
    printf("NOR Truth Table\n");
    printf("A | B | OUTPUT\n");
    printf("----------------\n");
    printf("0 | 0 |  1\n");
    printf("0 | 1 |  0\n");
    printf("1 | 0 |  0\n");
    printf("1 | 1 |  0\n");
}
void printXOR() {
    printf("XOR Truth Table\n");
    printf("A | B | OUTPUT\n");
    printf("----------------\n");
    printf("0 | 0 |  0\n");
    printf("0 | 1 |  1\n");
    printf("1 | 0 |  1\n");
    printf("1 | 1 |  0\n");
}
void printXNOR() {
    printf("XNOR Truth Table\n");
    printf("A | B | OUTPUT\n");
    printf("----------------\n");
    printf("0 | 0 |  1\n");
    printf("0 | 1 |  0\n");
    printf("1 | 0 |  0\n");
    printf("1 | 1 |  1\n");
}