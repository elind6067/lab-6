#include <stdio.h>
#include <stdlib.h>
#include "gates.h"
/*
    Ella Lind
    ECE 321L - 001
    Lab 7 - Logic Gate Simulator Part 3
    10/13/2025
    Description: This program simulates 2 circuits based on user input. 
    Added AND_N and OR_N functions so program can handle n inuputs for AND and OR gates. 
*/
# define n 8 // max number of inputs for AND_N and OR_N

// function prototypes
int CircuitN1(int A[], int B[]);
int CircuitN2(int A[], int B[]);

int main() {
    int A[n];
    int B[n];
    char m;
    int result;
    printf("Enter r to randomize bits or u to enter bit signals manually:\n");
    scanf(" %c", &m);
    if (m == 'u' || m == 'U') {
        printf("Enter %d inputs (0 or 1) for A:\n", n);
        for (int i = 0; i < n; i++) {
            scanf("%d", &A[i]);
            if (A[i] != 0 && A[i] != 1) {
                printf("Invalid input. Please enter 0 or 1\n");
            }
        }
        printf("Enter %d inputs (0 or 1) for B:\n", n);
        for (int i = 0; i < n; i++) {
            scanf("%d", &B[i]);
            if (B[i] != 0 && B[i] != 1) {
                printf("Invalid input. Please enter 0 or 1\n");
            }
        }
    }
    else if (m == 'r' || m == 'R') {
        printf("Randomizing %d inputs for A and B:\n", (n));
        for (int i = 0; i < n; i++) {
            A[i] = rand() % 2; // random 0 or 1
            B[i] = rand() % 2; 
        }
    }
    else {
        printf("Invalid input. Please enter r or u\n");
    }
    result = CircuitN1(A, B);
    //result = CircuitN2(A, B);
    printf("Result: %d\n", result);
    return 0;
}

int CircuitN1(int A[], int B[]){
    // split signals
    int arr[] = {A[0], A[1], A[2], A[3], B[0], B[1], B[2], B[3]};
    int brr[] = {A[4], A[5], A[6], A[7], B[4], B[5], B[6], B[7]};
    return BUFFER(XNOR(AND_N(arr, n), OR_N(brr, n)));
}
int CircuitN2(int A[], int B[]){
    // split signals
    int arr1[] = {A[12], A[13], A[14], A[15], B[0], B[1], B[2], B[3]};
    int brr1[] = {A[8], A[9], A[10], A[11], B[4], B[5], B[6], B[7]};
    int brr2[] = {A[4], A[5], A[6], A[7], B[8], B[9], B[10], B[11]};
    int arr2[] = {A[0], A[1], A[2], A[3], B[12], B[13], B[14], B[15]};
    return OR(OR(AND_N(arr1, n), OR_N(brr1, n)), AND(OR_N(brr2, n), AND_N(arr2, n)));
}