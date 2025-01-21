#include <stdio.h>
#include <stdlib.h>

void input(int matrix[10][10], int rows, int cols) { // INPUT
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }
}

void print(int matrix[10][10], int rows, int cols) { // PRINTING
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

int determinant(int mat[10][10], int n) { // DETERMINANT
    if (n == 1)
        return mat[0][0];
    int temp[10][10];
    int det = 0;
    int sign = 1;
    for (int f = 0; f < n; f++) {
        // Creating minor matrix
        int minorRow = 0, minorCol = 0;
        for (int i = 1; i < n; i++) { 
            for (int j = 0; j < n; j++) {
                if (j != f) { // 
                    temp[minorRow][minorCol++] = mat[i][j];
                    if (minorCol == n - 1) {
                        minorCol = 0;
                        minorRow++;
                    }
                }
            }
        }
        det += sign * mat[0][f] * determinant(temp, n - 1);
        sign = -sign;
    }
    return det;
}

void findCofactor(int n, int matrix[10][10], int cofactor[10][10]) { // COFACTOR
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int minor[10][10];
            int minorRow = 0, minorCol = 0;

            for (int x = 0; x < n; x++) {
                for (int y = 0; y < n; y++) {
                    if (x != i && y != j) {
                        minor[minorRow][minorCol] = matrix[x][y];
                        minorCol++;
                        if (minorCol == n - 1) {
                            minorCol = 0;
                            minorRow++;
                        }
                    }
                }
            }

            // det of minor
            int determinant = (minor[0][0] * minor[1][1]) - (minor[0][1] * minor[1][0]);

            if ((i + j) % 2 == 0) {
                cofactor[i][j] = determinant;
            } else {
                cofactor[i][j] = -determinant;
            }
        }
    }
}

void transpose(int n, int matrix[10][10], int result[10][10]) { // TRANSPOSE
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            result[j][i] = matrix[i][j];
        }
    }
}

void computeAdjoint(int n, int mat[10][10], int adj[10][10]) { // ADJOINT
    int cofactor[10][10];
    findCofactor(n, mat, cofactor);
    transpose(n, cofactor, adj);
}

void inverse(int mat[10][10], int n) { // INVERSE
    int det = determinant(mat, n);
    if (det == 0) {
        printf("The matrix is singular and cannot have an inverse.\n");
        return;
    }
    int adj[10][10];
    computeAdjoint(n, mat, adj);
    printf("The inverse of the matrix is:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%.2f ", (float)adj[i][j] / det);
        }
        printf("\n");
    }
}

void addsubtract(int matA[10][10], int matB[10][10], int result[10][10], int rows, int cols, int isAddition) { // ADD/SUB
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result[i][j] = isAddition ? matA[i][j] + matB[i][j] : matA[i][j] - matB[i][j];
        }
    }
}

void multiply(int first[10][10], int second[10][10], int result[10][10], int row1, int col1, int col2) { // MULTIPLY
    for (int i = 0; i < row1; i++) {
        for (int j = 0; j < col2; j++) {
            result[i][j] = 0;
            for (int k = 0; k < col1; k++) {
                result[i][j] += first[i][k] * second[k][j];
            }
        }
    }
}

int trace(int matrix[10][10], int n) { // TRACE
    int trace = 0;
    for (int i = 0; i < n; i++) {
        trace += matrix[i][i];
    }
    return trace;
}

int main() {
    int choice;
    printf("Matrix Calculator:\n");
    printf("1. Determinant\n");
    printf("2. Adjoint\n");
    printf("3. Inverse\n");
    printf("4. Multiplication\n");
    printf("5. Trace\n");
    printf("6. Addition\n");
    printf("7. Subtraction\n\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    if (choice == 1 || choice == 2 || choice == 3 || choice == 5) {
        int n;
        printf("\nEnter the order of the square matrix: ");
        scanf("%d", &n);
        int mat[10][10];
        printf("\nEnter the elements of the matrix:\n");
        input(mat, n, n);
        if (choice == 1) {
            printf("\nDeterminant: %d\n", determinant(mat, n));
        } else if (choice == 2) {
            int adj[10][10];
            computeAdjoint(n, mat, adj);
            printf("\nAdjoint of the matrix:\n");
            print(adj, n, n);
        } else if (choice == 3) {
            inverse(mat, n);
        } else if (choice == 5) {
            printf("\nTrace: %d\n", trace(mat, n));
        }
    } else if (choice == 4) {
        int r1, c1, r2, c2;
        printf("\nEnter dimensions for the first matrix (rows cols): ");
        scanf("%d %d", &r1, &c1);
        printf("\nEnter dimensions for the second matrix (rows cols): ");
        scanf("%d %d", &r2, &c2);
        if (c1 != r2) {
            printf("\nIncompatible dimensions for multiplication.\n");
            return 0;
        }
        int first[10][10], second[10][10], result[10][10];
        printf("\nEnter elements of the first matrix:\n");
        input(first, r1, c1);
        printf("\nEnter elements of the second matrix:\n");
        input(second, r2, c2);
        multiply(first, second, result, r1, c1, c2);
        printf("\nResultant matrix:\n");
        print(result, r1, c2);
    } else if (choice == 6 || choice == 7) {
        int rows, cols;
        printf("\nEnter dimensions of the matrices (rows cols): ");
        scanf("%d %d", &rows, &cols);
        int matA[10][10], matB[10][10], result[10][10];
        printf("\nEnter elements of the first matrix:\n");
        input(matA, rows, cols);
        printf("\nEnter elements of the second matrix:\n");
        input(matB, rows, cols);
        addsubtract(matA, matB, result, rows, cols, choice == 6);
        printf("\nResultant matrix:\n");
        print(result, rows, cols);
    } else {
        printf("\nInvalid choice.\n");
    }
    return 0;
}
