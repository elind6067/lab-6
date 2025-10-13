#include <stdio.h>
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
int CircuitN1(int arr[], int size);
int CircuitN2(int arr[], int size);

int main() {
    int A[n/2];
    int B[n/2];
    char m;
    printf("Enter r to randomize bits or u to enter bit signals manually:\n");
    scanf(" %c", &m);
    if (m == 'u' || m == 'U') {
        printf("Enter %d inputs (0 or 1) for A:\n", (n/2));
        for (int i = 0; i < n; i++) {
            scanf("%d", &A[i]);
            if (A[i] != 0 && A[i] != 1) {
                printf("Invalid input. Please enter 0 or 1\n");
            }
        }
        printf("Enter %d inputs (0 or 1) for B:\n", (n/2));
        for (int i = 0; i < n; i++) {
            scanf("%d", &B[i]);
            if (B[i] != 0 && B[i] != 1) {
                printf("Invalid input. Please enter 0 or 1\n");
            }
        }
    }
    else if (m == 'r' || m == 'R') {
        printf("Randomizing %d inputs for A and B:\n", (n/2));
        for (int i = 0; i < n/2; i++) {
            A[i] = rand() % 2; // random 0 or 1
            B[i] = rand() % 2; // random 0 or 1
        }
    }
    else {
        printf("Invalid input. Please enter r or u\n");
    }
    return 0;
}

int CircuitN1(int arr[], int size){
    return AND_N(arr, n);
}
int CircuitN2(int arr[], int size){
    return OR_N(arr, n);
}