#include <stdio.h>
#include <stdlib.h>

int *File_read(int *n);
int Determinant(int *matrix, int n);
int *Cutter(int *mat, int k, int l, int n);
void File_write(int* matrix, int det, int n);

int main() {
    int n = -1;
    int *matrix = File_read(&n);

    int result = Determinant(matrix, n);

    File_write(matrix, result, n);

    return 0;
}

int *File_read(int *n) {
    FILE *Matrix;
    Matrix = fopen("Matrix.txt", "r");

    *n = fgetc(Matrix) - 48;
    fgetc(Matrix);
    unsigned int N = (unsigned int) *n;

    int *matrix_in_line = calloc (N*N, sizeof(int));
    int j = 0;
    char c[10];
    while (j < N*N) {
        fscanf(Matrix, "%s", c);
        matrix_in_line[j] = (int) strtol(c, NULL, 0);
        j++;
    }

    fclose(Matrix);

    return matrix_in_line;
}

int Determinant(int *matrix, int n) {
    if (n == 1) {
        return matrix[0];
    }

    int i = 0;
    long int result = 0;
    for ( ; i < n; i++) {
        if (matrix[i] == 0) {
            continue;
        }
        int *a_mat = Cutter(matrix, i/n, i%n, n-1);
        if (i % 2 == 0) {
            result += matrix[i] * Determinant(a_mat, n-1);
        }
        else {
            result -= matrix[i] * Determinant(a_mat, n-1);
        }
    }

    return result;
}

int *Cutter(int *mat, int k, int l, int n) {
    int *cut_mat = calloc(n*n, sizeof(int));

    int i = 0, j = 0, e = 0;
    while (i < n*n) {
        if (j != k && e != l) {
            cut_mat[i] = mat[j*(n+1) + e];
            i++;
        }
        e++;
        if (e == (n+1) && j < (n+1)) {
            e = 0;
            j++;
        }
    }

    return cut_mat;
}

void File_write(int *matrix, int det, int n) {
    FILE *answer;
    answer = fopen("Result.txt", "a");

    fprintf(answer, "The matrix:\n");
    int v = 0, u = 0;
    for ( ; v < n; v++) {
        for ( ; u < n; u++) {
            fprintf(answer, "%4d ", matrix[v*n + u]);
        }
        u = 0;
        fprintf(answer, "\n");
    }

    fprintf(answer, "The determinant: %d\n\n", det);
}