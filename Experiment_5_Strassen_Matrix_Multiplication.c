#include <stdio.h>
#include <stdlib.h>

void sumMatrix(int **A, int **B, int **Result, int n)
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            Result[i][j] = A[i][j] + B[i][j];
}

void subtractMatrix(int **A, int **B, int **Result, int n)
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            Result[i][j] = A[i][j] - B[i][j];
}

int **allocateMatrix(int n)
{
    int **matrix = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++)
        matrix[i] = (int *)malloc(n * sizeof(int));
    return matrix;
}

void freeMatrix(int **matrix, int n)
{
    for (int i = 0; i < n; i++)
        free(matrix[i]);
    free(matrix);
}

void strassen(int **A, int **B, int **C, int n)
{
    if (n == 1)
    {
        C[0][0] = A[0][0] * B[0][0];
    }
    else
    {
        int newSize = n / 2;
        int **A11 = allocateMatrix(newSize);
        int **A12 = allocateMatrix(newSize);
        int **A21 = allocateMatrix(newSize);
        int **A22 = allocateMatrix(newSize);
        int **B11 = allocateMatrix(newSize);
        int **B12 = allocateMatrix(newSize);
        int **B21 = allocateMatrix(newSize);
        int **B22 = allocateMatrix(newSize);

        int **C11 = allocateMatrix(newSize);
        int **C12 = allocateMatrix(newSize);
        int **C21 = allocateMatrix(newSize);
        int **C22 = allocateMatrix(newSize);

        int **M1 = allocateMatrix(newSize);
        int **M2 = allocateMatrix(newSize);
        int **M3 = allocateMatrix(newSize);
        int **M4 = allocateMatrix(newSize);
        int **M5 = allocateMatrix(newSize);
        int **M6 = allocateMatrix(newSize);
        int **M7 = allocateMatrix(newSize);

        int **tempA = allocateMatrix(newSize);
        int **tempB = allocateMatrix(newSize);

        // Dividing matrices into 4 sub-matrices
        for (int i = 0; i < newSize; i++)
        {
            for (int j = 0; j < newSize; j++)
            {
                A11[i][j] = A[i][j];
                A12[i][j] = A[i][j + newSize];
                A21[i][j] = A[i + newSize][j];
                A22[i][j] = A[i + newSize][j + newSize];

                B11[i][j] = B[i][j];
                B12[i][j] = B[i][j + newSize];
                B21[i][j] = B[i + newSize][j];
                B22[i][j] = B[i + newSize][j + newSize];
            }
        }

        // Calculating M1 to M7:
        sumMatrix(A11, A22, tempA, newSize); // A11 + A22
        sumMatrix(B11, B22, tempB, newSize); // B11 + B22
        strassen(tempA, tempB, M1, newSize); // M1 = (A11+A22) * (B11+B22)

        sumMatrix(A21, A22, tempA, newSize); // A21 + A22
        strassen(tempA, B11, M2, newSize);   // M2 = (A21+A22) * (B11)

        subtractMatrix(B12, B22, tempB, newSize); // B12 - B22
        strassen(A11, tempB, M3, newSize);        // M3 = (A11) * (B12 - B22)

        subtractMatrix(B21, B11, tempB, newSize); // B21 - B11
        strassen(A22, tempB, M4, newSize);        // M4 = (A22) * (B21 - B11)

        sumMatrix(A11, A12, tempA, newSize); // A11 + A12
        strassen(tempA, B22, M5, newSize);   // M5 = (A11+A12) * (B22)

        subtractMatrix(A21, A11, tempA, newSize); // A21 - A11
        sumMatrix(B11, B12, tempB, newSize);      // B11 + B12
        strassen(tempA, tempB, M6, newSize);      // M6 = (A21-A11) * (B11+B12)

        subtractMatrix(A12, A22, tempA, newSize); // A12 - A22
        sumMatrix(B21, B22, tempB, newSize);      // B21 + B22
        strassen(tempA, tempB, M7, newSize);      // M7 = (A12-A22) * (B21+B22)

        // Calculating C11, C12, C21, C22:
        sumMatrix(M1, M4, tempA, newSize);         // M1 + M4
        subtractMatrix(tempA, M5, tempB, newSize); // M1 + M4 - M5
        sumMatrix(tempB, M7, C11, newSize);        // C11 = M1 + M4 - M5 + M7

        sumMatrix(M3, M5, C12, newSize); // C12 = M3 + M5
        sumMatrix(M2, M4, C21, newSize); // C21 = M2 + M4

        sumMatrix(M1, M3, tempA, newSize);         // M1 + M3
        subtractMatrix(tempA, M2, tempB, newSize); // M1 + M3 - M2
        sumMatrix(tempB, M6, C22, newSize);        // C22 = M1 + M3 - M2 + M6

        // Grouping the results back into a single matrix:
        for (int i = 0; i < newSize; i++)
        {
            for (int j = 0; j < newSize; j++)
            {
                C[i][j] = C11[i][j];
                C[i][j + newSize] = C12[i][j];
                C[i + newSize][j] = C21[i][j];
                C[i + newSize][j + newSize] = C22[i][j];
            }
        }

        // Freeing all allocated memory
        freeMatrix(A11, newSize);
        freeMatrix(A12, newSize);
        freeMatrix(A21, newSize);
        freeMatrix(A22, newSize);
        freeMatrix(B11, newSize);
        freeMatrix(B12, newSize);
        freeMatrix(B21, newSize);
        freeMatrix(B22, newSize);
        freeMatrix(C11, newSize);
        freeMatrix(C12, newSize);
        freeMatrix(C21, newSize);
        freeMatrix(C22, newSize);
        freeMatrix(M1, newSize);
        freeMatrix(M2, newSize);
        freeMatrix(M3, newSize);
        freeMatrix(M4, newSize);
        freeMatrix(M5, newSize);
        freeMatrix(M6, newSize);
        freeMatrix(M7, newSize);
        freeMatrix(tempA, newSize);
        freeMatrix(tempB, newSize);
    }
}

void printMatrix(int **matrix, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            printf("%d ", matrix[i][j]);
        printf("\n");
    }
}

int main()
{
    int n = 4; // Example size, should be a power of 2
    int **A, **B, **C;

    A = allocateMatrix(n);
    B = allocateMatrix(n);
    C = allocateMatrix(n);

    // Assuming some initialization of matrices A and B
    // For simplicity, let's initialize A and B with some values
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            A[i][j] = i + j; // Example initialization
            B[i][j] = i - j; // Example initialization
        }
    }

    printf("Matrix A:\n");
    printMatrix(A, n);
    printf("Matrix B:\n");
    printMatrix(B, n);

    strassen(A, B, C, n);

    printf("Result matrix C after Strassen's Matrix Multiplication:\n");
    printMatrix(C, n);

    // Free allocated memory
    freeMatrix(A, n);
    freeMatrix(B, n);
    freeMatrix(C, n);

    return 0;
}
