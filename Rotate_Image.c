/*Problem 1: Rotate Image (Array/Pointers)

Description:

You are given an n x n 2D matrix representing an image. Rotate the image by 90 degrees (clockwise).

You have to rotate the image in-place, which means you have to modify the input 2D matrix directly. DO NOT allocate another 2D matrix and do the rotation.

Function Signature:

void rotate(int** matrix, int matrixSize, int* matrixColSize);
Example 1:

Input: matrix = [[1,2,3],[4,5,6],[7,8,9]] Output: [[7,4,1],[8,5,2],[9,6,3]]

!Rotate 1

Example 2:

Input: matrix = [[5,1,9,11],[2,4,8,10],[13,3,6,7],[15,14,12,16]] Output: [[15,13,2,5],[14,3,4,1],[12,6,8,9],[16,7,10,11]]

!Rotate 2

Constraints:

matrix.length == n
matrix[i].length == n
1 <= n <= 20
-1000 <= matrix[i][j] <= 1000
Hint: A common approach is to first transpose the matrix and then reverse each row. This can be done efficiently in-place.*/
#include <stdio.h>
#include <stdlib.h>

void rotate(int** matrix, int matrixSize, int* matrixColSize){
    int** m = malloc(matrixSize * sizeof(int*));
    for (int i=0; i< *matrixColSize; i++){
        m[i] = malloc(matrixSize * sizeof(int));
        for(int j=0; j<matrixSize; j++){
            m[j][i] = matrix[i][j];

        }

    }
    matrix = m;



}

void free_matrix(int** m, int n) {
    for (int i = 0; i < n; i++) free(m[i]);
    free(m);
}

int** make_matrix(int flat[], int n) {
    int** m = malloc(n * sizeof(int*));
    for(int i=0; i<n; i++){
        m[i] = malloc(n* sizeof(int));
        for(int j=0; j<n; j++){
            m[i][j]= flat[i*n+j];

        }

    }
return m;
}

void print_matrix(int **m, int n, const char* label){
    printf("%s\n", label);
    for(int i=0; i<n; i++){
        printf(" [");
        for(int j=0; j<n; j++){
            printf("%d%s" , m[i][j], j < n-1 ? "," : "");
        }
        printf("]\n");
    }
    printf("\n");

}
void run_test(const char* name, int flat[], int n) {
    int* colSize = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) colSize[i] = n;

    int** matrix = make_matrix(flat, n);

    printf("=== %s ===\n", name);
    print_matrix(matrix, n, "Before:");

    rotate(matrix, n, colSize);

    print_matrix(matrix, n, "After:");

    free_matrix(matrix, n);
    free(colSize);
}

int main(void) {
    /* Example 1: 3×3 */
    int e1[] = {1,2,3,
                4,5,6,
                7,8,9};
    run_test("Example 1 (3x3)", e1, 3);

    /* Example 2: 4×4 */
    int e2[] = { 5, 1, 9,11,
                 2, 4, 8,10,
                13, 3, 6, 7,
                15,14,12,16};
    run_test("Example 2 (4x4)", e2, 4);

    return 0;
}
