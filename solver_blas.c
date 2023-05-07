/*
 * Tema 2 ASC
 * 2023 Spring
 */

#include "utils.h"
#include <string.h>
#include <stdlib.h>
#include <float.h>

#include "cblas.h"

void allocate_matrices(int N, double **result_matrix, double **A_times_A) {
    *result_matrix = (double*) malloc(N * N * sizeof(double));
    *A_times_A = (double*) malloc(N * N * sizeof(double));
}

double* my_solver(int N, double *A, double *B) {
    double *result_matrix, *A_times_A;
    allocate_matrices(N, &result_matrix, &A_times_A);
    
    if (result_matrix == NULL || A_times_A == NULL) {
        // memory allocation failed
        free(result_matrix);
        free(A_times_A);
        return NULL;
    }

    // Calculate C = B * A^T using dtrmm and dgemm
    cblas_dtrmm(CblasRowMajor, CblasLeft, CblasUpper, CblasNoTrans, CblasNonUnit, N, N, 1.0, A, N, B, N);
    cblas_dtrmm(CblasRowMajor, CblasRight, CblasUpper, CblasTrans, CblasNonUnit, N, N, 1.0, A, N, B, N);
    cblas_dgemm(CblasRowMajor, CblasTrans, CblasTrans, N, N, N, 1.0, B, N, B, N, 1.0, A_times_A, N);

    // Calculate C += A^2 * B using daxpy
    for (int i = 0; i < N; i++) {
        cblas_daxpy(N, 1.0, A_times_A + i * N, 1, result_matrix + i * N, 1);
    }

    free(A_times_A);

    // Check for NaN or infinity values in the result matrix
    for (int i = 0; i < N * N; i++) {
        if (!(result_matrix[i] == result_matrix[i]) || result_matrix[i] > DBL_MAX || result_matrix[i] < -DBL_MAX) {
            free(result_matrix);
            return NULL;
        }
    }

    return result_matrix;
}
