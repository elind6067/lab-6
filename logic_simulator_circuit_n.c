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

int CircuitN1(int arr[], int size){
    return AND_N(arr, n);
}
int CircuitN2(int arr[], int size){
    return OR_N(arr, n);
}