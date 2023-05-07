/*
 * Tema 2 ASC
 * 2023 Spring
 */
#include <string.h>
#include <stdlib.h>

#include "cblas.h"

int allocate_matrices(int N, double **result_matrix, double **A_times_A) {
    // Calculate the size of a matrix with N rows and N columns in bytes.
    int size = N * N * sizeof(double);

    // Allocate memory for result_matrix and check if the allocation was successful.
    *result_matrix = malloc(size);
    if (*result_matrix == NULL)
        return -1;

    // Allocate memory for A_times_A and check if the allocation was successful.
    *A_times_A = malloc(size);
    if (*A_times_A == NULL) {
        free(*result_matrix); // Free the previously allocated memory.
        return -1;
    }

    return 0;
}

double *my_solver(int N, double *A, double *B) {
	int res;
    double *result_matrix, *A_times_A;

    // Allocate memory for result_matrix and A_times_A
    res = allocate_matrices(N, &result_matrix, &A_times_A);

	if (res == -1) {
		// printf("Error: failed to allocate memory");
		return 0;
	}

    // Calculate C = B * A^T using dgemm
    cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasTrans, N, N, N, 1.0, B, N, A, N, 0.0, result_matrix, N);

    // Calculate A_times_A = A * A using dsyrk
    cblas_dsyrk(CblasRowMajor, CblasUpper, CblasNoTrans, N, N, 1.0, A, N, 0.0, A_times_A, N);

    // Calculate B = A^2 * B using dtrmm
    cblas_dtrmm(CblasRowMajor, CblasLeft, CblasUpper, CblasNoTrans, CblasNonUnit, N, N, 1.0, A_times_A, N, B, N);

    // Calculate C += A^2 * B using daxpy
    cblas_daxpy(N * N, 1.0, B, 1, result_matrix, 1);

    // Free memory for A_times_A
    free(A_times_A);

    // Return the result
    return result_matrix;
}