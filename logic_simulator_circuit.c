#include <stdio.h>
#include "gates.h"
/*
    Ella Lind
    ECE 321L - 001
    Lab 6 - Logic Gate Simulator Part 2
    10/6/2025
    Description: This program simulates 2 circuits based on user input.
*/

// function prototypes
int Circuit1(int a, int b);
int Circuit2(int a, int b);

int main() {
    int a, b, result;
    printf("Enter inputs a and b for Circuit 1:\n");
    scanf("%d %d", &a, &b);
    if ((a == 0 || a == 1 ) && (b == 0 || b == 1)) { // check for valid input
        result = Circuit1(a, b);
        printf("Circuit 1 with inputs a = %d and b = %d yields output: %d\n", a, b, result);
    }
    else {
        printf("Invalid input. Please enter 0 or 1 for a and b\n");
    }
    printf("Enter inputs a and b for Circuit 2:\n");
    scanf("%d %d", &a, &b);
    if ((a == 0 || a == 1 ) && (b == 0 || b == 1)) { // check for valid input
        result = Circuit2(a, b);
        printf("Circuit 2 with inputs a = %d and b = %d yields output: %d\n", a, b, result);
    }
    else {
        printf("Invalid input. Please enter 0 or 1 for a and b\n");
    }
    return 0;
}

int Circuit1(int a, int b){
    return OR(AND(a, b), AND(NOT(a), NOT(b)));
}
int Circuit2(int a, int b){
    return OR(AND(NOT(a), b), AND(a, NOT(b)));
}