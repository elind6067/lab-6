#ifndef GATES_H
#define GATES_H
/*
    function prototypes for gates.c
*/
int NOT(int a);
int AND(int a, int b);
int OR(int a, int b);
int NAND(int a, int b);
int NOR(int a, int b);
int XOR(int a, int b);
int XNOR(int a, int b);
int AND_N(int arr[], int n);
int OR_N(int arr[], int n);
#endif // GATES_H  