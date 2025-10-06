#include <stdio.h>

/*
    gate function definitions
    assuming inputs are integers either 0 or 1
*/

int NOT(int a) {
    return !a;
}
int AND(int a, int b) {
    return a && b;
}
int OR(int a, int b) {
    return a || b;
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