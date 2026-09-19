/*Problem: Dynamic Array Creation and Population
Description:

Write a C program that accomplishes the following tasks:

Declare an integer pointer.
Dynamically allocate memory for an array of 3 integers using malloc.
Check if the memory allocation was successful. If not, print an error and exit.
Populate the allocated array with the integer values 1, 2, and 3.
Print the contents of the array to the console.
Ensure you free the dynamically allocated memory before the program terminates to prevent memory leaks*/

#include <stdio.h>
#include <stdlib.h>

int main() {
    int n = 3;
    
    // 1. Allocate memory for 'n' integers
    int *arr = (int *)malloc(n * sizeof(int));
    
    // 2. Always check if the allocation was successful
    if (arr == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }
    
    // 3. Use it exactly like a normal array
    for (int i = 0; i < n; i++) {
        arr[i] = (i + 1) * 10;
        printf("%d ", arr[i]);
    }
    printf("\n");

    // accessing it via pointer
    int *ptr = arr;          // separate pointer for walking
    for (int i = 0; i < n; i++) {
        printf("%d ", *ptr);
        ptr += 1;            // move ptr, not arr
    }

    free(arr);               // arr still points to start — safe
    arr = NULL;

    
    return 0;
}



