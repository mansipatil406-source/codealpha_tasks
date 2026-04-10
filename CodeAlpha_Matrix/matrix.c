#include <stdio.h>

#define MAX 10

// Function to input matrix
void inputMatrix(int matrix[MAX][MAX], int row, int col) {
    int i, j;
    for(i = 0; i < row; i++) {
        for(j = 0; j < col; j++) {
            printf("Enter element [%d][%d]: ", i, j);
            scanf("%d", &matrix[i][j]);
        }
    }
}

// Function to display matrix
void displayMatrix(int matrix[MAX][MAX], int row, int col) {
    int i, j;
    for(i = 0; i < row; i++) {
        for(j = 0; j < col; j++) {
            printf("%d\t", matrix[i][j]);
        }
        printf("\n");
    }
}

// Function for matrix addition
void addMatrix(int A[MAX][MAX], int B[MAX][MAX], int row, int col) {
    int result[MAX][MAX];
    int i, j;

    for(i = 0; i < row; i++) {
        for(j = 0; j < col; j++) {
            result[i][j] = A[i][j] + B[i][j];
        }
    }

    printf("\nResult of Addition:\n");
    displayMatrix(result, row, col);
}

// Function for matrix multiplication
void multiplyMatrix(int A[MAX][MAX], int B[MAX][MAX], int r1, int c1, int r2, int c2) {
    int result[MAX][MAX] = {0};
    int i, j, k;

    if(c1 != r2) {
        printf("Matrix multiplication not possible!\n");
        return;
    }

    for(i = 0; i < r1; i++) {
        for(j = 0; j < c2; j++) {
            for(k = 0; k < c1; k++) {
                result[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    printf("\nResult of Multiplication:\n");
    displayMatrix(result, r1, c2);
}

// Function for transpose
void transposeMatrix(int matrix[MAX][MAX], int row, int col) {
    int transpose[MAX][MAX];
    int i, j;

    for(i = 0; i < row; i++) {
        for(j = 0; j < col; j++) {
            transpose[j][i] = matrix[i][j];
        }
    }

    printf("\nTranspose of Matrix:\n");
    displayMatrix(transpose, col, row);
}

int main() {
    int A[MAX][MAX], B[MAX][MAX];
    int r1, c1, r2, c2;
    int choice;

    printf("Enter rows and columns of Matrix A: ");
    scanf("%d %d", &r1, &c1);

    printf("Enter elements of Matrix A:\n");
    inputMatrix(A, r1, c1);

    printf("Enter rows and columns of Matrix B: ");
    scanf("%d %d", &r2, &c2);

    printf("Enter elements of Matrix B:\n");
    inputMatrix(B, r2, c2);

    do {
        printf("\n===== Matrix Operations Menu =====\n");
        printf("1. Matrix Addition\n");
        printf("2. Matrix Multiplication\n");
        printf("3. Transpose of Matrix A\n");
        printf("4. Display Matrices\n");
        printf("0. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                if(r1 == r2 && c1 == c2) {
                    addMatrix(A, B, r1, c1);
                } else {
                    printf("Addition not possible! Dimensions must be same.\n");
                }
                break;

            case 2:
                multiplyMatrix(A, B, r1, c1, r2, c2);
                break;

            case 3:
                transposeMatrix(A, r1, c1);
                break;

            case 4:
                printf("\nMatrix A:\n");
                displayMatrix(A, r1, c1);
                printf("\nMatrix B:\n");
                displayMatrix(B, r2, c2);
                break;

            case 0:
                printf("Exiting program...\n");
                break;

            default:
                printf("Invalid choice!\n");
        }

    } while(choice != 0);

    return 0;
}
