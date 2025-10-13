#include <stdio.h>

/*
    gate function definitions
    assuming inputs are integers either 0 or 1
*/

int NOT(int a) {
    return !a;
}
int AND(int a, int b) {
    return (a && b);
}
int OR(int a, int b) {
    return (a || b);
}
int NAND(int a, int b) {
    return !(a && b);
}
int NOR(int a, int b) {
    return !(a || b);
}
int XOR(int a, int b) {
    if(a == b) {
        return 0;
    } else {
        return 1;
    }
}
int XNOR(int a, int b) {
    if(a == b) {
        return 1;
    } else {
        return 0;
    }
}

int AND_N(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        if (arr[i] == 0) { // if there are any 0s, return 0
            return 0;
        }
    }
    return 1; // if all 1s, return 1
}
int OR_N(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        if (arr[i] == 1) { // if there are any 1s, return 1
            return 1;
        }
    }
    return 0; // if all 0s, return 0
}
int BUFFER(int a) {
    return a;
}