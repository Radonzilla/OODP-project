#include <stdio.h>

void input(int matrix[10][10], int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }
}

void print(int matrix[10][10], int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

// cofactor 
void cofactor(int mat[10][10], int temp[10][10], int p, int q, int n) {
    int i = 0, j = 0;
    for (int row = 0; row < n; row++) {
        for (int col = 0; col < n; col++) {
            if (row != p && col != q) {
                temp[i][j] = mat[row][col];
                j++;
                if (j == n - 1) {
                    j = 0;
                    i++;
                }
            }
        }
    }
}

// determinant
int determinant(int mat[10][10], int n) {
    if (n == 1) {
        return mat[0][0];
    }
    int temp[10][10];
    int det = 0;
    int sign = 1;

    for (int f = 0; f < n; f++) {
        cofactor(mat, temp, 0, f, n);
        det += sign * mat[0][f] * determinant(temp, n - 1);
        sign = -sign;
    }
    return det;
}

// transpose
void transpose(int n, int matrix[10][10], int result[10][10]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            result[j][i] = matrix[i][j];
        }
    }
}

// adjoint
void adjoint(int mat[10][10], int adj[10][10], int n) {
    if (n == 1) {
        adj[0][0] = 1;
        return;
    }

    int temp[10][10];
    int sign = 1;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cofactor(mat, temp, i, j, n);
            int det = determinant(temp, n - 1);
            sign = ((i + j) % 2 == 0) ? 1 : -1;
            adj[j][i] = sign * det;  // 
        }
    }
}

// inverse ...
void inverse(int mat[10][10], int n) {
    int det = determinant(mat, n);
    if (det == 0) {
        printf("The matrix is singular and cannot have an inverse.\n");
        return;
    }

    int adj[10][10];
    adjoint(mat, adj, n);

    printf("The inverse of the matrix is:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%.2f ", (float)adj[i][j] / det);
        }
        printf("\n");
    }
}

// add and subtract
void addsubtract(int matA[10][10], int matB[10][10], int result[10][10], int rows, int cols, int isAddition) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result[i][j] = isAddition ? matA[i][j] + matB[i][j] : matA[i][j] - matB[i][j];
        }
    }
}

// Multiply
void multiply(int first[10][10], int second[10][10], int result[10][10], int row1, int col1, int col2) {
    for (int i = 0; i < row1; i++) {
        for (int j = 0; j < col2; j++) {
            result[i][j] = 0;
            for (int k = 0; k < col1; k++) {
                result[i][j] += first[i][k] * second[k][j];
            }
        }
    }
}

// trace
int trace(int matrix[10][10], int n) {
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
            adjoint(mat, adj, n);
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
//
