#include "graph_math.h"

void solveSparseSystem(Node *matrix, int nnz, double *b, double *x, int n) {
    double *x_new = (double *)malloc(n * sizeof(double));

    for (int iter = 0; iter < MAX_ITER; iter++) {
        for (int i = 0; i < n; i++) x_new[i] = b[i];

        for (int k = 0; k < nnz; k++) {
            int row = matrix[k].position / n;
            int col = matrix[k].position % n;

            if (row == col) continue;

            x_new[row] -= matrix[k].value * x[col];
        }

        for (int k = 0; k < nnz; k++) {
            int row = matrix[k].position / n;
            int col = matrix[k].position % n;

            if (row == col) {
                if (fabs(matrix[k].value) < 1e-12) {
                    printf("Matrix is singular or nearly singular.\n");
                    exit(1);
                }
                x_new[row] /= matrix[k].value;
            }
        }

        double max_diff = 0.0;
        for (int i = 0; i < n; i++) {
            max_diff = fmax(max_diff, fabs(x_new[i] - x[i]));
            x[i] = x_new[i];
        }
        if (max_diff < TOL) break;
    }

    free(x_new);
}

void normalize(double *v, int n) {
    double norm = 0;
    for (int i = 0; i < n; i++) norm += v[i] * v[i];
    norm = sqrt(norm);

    if (norm < 1e-12) {
        printf("Warning: Zero norm encountered during normalization.\n");
        exit(1);
    }

    for (int i = 0; i < n; i++) v[i] /= norm;
}

double dotProduct(double *v1, double *v2, int n) {
    double sum = 0;
    for (int i = 0; i < n; i++) sum += v1[i] * v2[i];
    return sum;
}

void inversePowerMethod(Node *matrix, int nnz, double *eigenvector, double *eigenvalue, int n) {
    double *y = malloc(n * sizeof(double));
    double *x = malloc(n * sizeof(double));

    // Inicjalizacja z losowym wektorem
    for (int i = 0; i < n; i++) x[i] = ((double)rand() / RAND_MAX) * 2.0 - 1.0;
    normalize(x, n);

    double lambda_old = 0, lambda_new = 0;
    int iter = 0;

    while (iter < MAX_ITER) {
        // Rozwiązuje (A * y) = x
        solveSparseSystem(matrix, nnz, x, y, n);

        normalize(y, n);

				// aproksymacja wartości własney metodą raylight
        lambda_new = dotProduct(y, x, n);

        if (fabs(lambda_new - lambda_old) < TOL) break;

        lambda_old = lambda_new;

		// Nowe x do następnej iteracji
        for (int i = 0; i < n; i++) x[i] = y[i];

        iter++;
    }

    if (fabs(lambda_new) < 1e-12) {
        printf("Wartość własna jest zbyt bliska zeru.\n");
        exit(1);
    }

    *eigenvalue = 1.0 / lambda_new;

    for (int i = 0; i < n; i++) eigenvector[i] = y[i];

    free(y);
    free(x);
}
