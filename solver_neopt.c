/*
 * Tema 2 ASC
 * 2023 Spring
 */
#include "utils.h"

/* Memory */
void alloc_matrix(int N, double **result_matrix, double **B_transpose,
					   double **A_square, double **A_square_x_B);
void dealloc_matrix(double *B_transpose, double *A_square, double *A_square_x_B);

/* Compute */
void compute_transpose(int N, double *B, double *B_transpose);
void compute_square(int N, double *A, double *A_square);
void compute_product(int N, double *A_square, double *B, double *A_square_x_B);
void compute_sum(int N, double *A, double *B, double *C);

double *my_solver(int N, double *A, double *B)
{
    double *result_matrix;		// Output matrix C
    double *B_transpose;		// Transpose of matrix B
    double *A_square;			// Square of matrix A
    double *A_square_x_B;    	// Product of A^2 and B

    alloc_matrix(N, &result_matrix, &B_transpose, &A_square, &A_square_x_B);

    /* Compute the transpose of matrix B */
    compute_transpose(N, B, B_transpose);

    /* Compute the square of matrix A */
    compute_square(N, A, A_square);

    /* Compute the product of A^2 and B */
    compute_product(N, A_square, B, A_square_x_B);

    /* Compute the sum of B_transpose and A_square_x_B */
    compute_sum(N, B_transpose, A_square_x_B, result_matrix);

    /* Free the memory allocated for the auxiliary matrices */
    dealloc_matrix(B_transpose, A_square, A_square_x_B);

    return result_matrix;
}

/* This function allocates memory for four matrices:
result_matrix, B_transpose, A_square, and A_square_x_B. 
It takes in an integer N, which specifies the dimensions of the matrices,
and three double pointer variables, which will point to the allocated
memory for each matrix. */
void alloc_matrix(int N, double **result_matrix, double **B_transpose,
					   double **A_square, double **A_square_x_B) {

	// Allocate memory for result_matrix
    *result_matrix = malloc(N * N * sizeof(double));
	// Check if allocation was successful
    if (*result_matrix == NULL) {
        // printf("Error: failed to allocate memory for result_matrix.\n");
        // Exit program with failure status
		exit(EXIT_FAILURE);
    }

	// Allocate memory for B_transpose
    *B_transpose = malloc(N * N * sizeof(double)); // Allocate memory for B_transpose
	// Check if allocation was successful
    if (*B_transpose == NULL) {
        // printf("Error: failed to allocate memory for B_transpose.\n");
        // Free previously allocated memory for result_matrix
		free(*result_matrix);
        // Exit program with failure status
		exit(EXIT_FAILURE);
    }

	// Allocate memory for A_square
    *A_square = malloc(N * N * sizeof(double)); // Allocate memory for A_square
	// Check if allocation was successful
    if (*A_square == NULL) {
        // printf("Error: failed to allocate memory for A_square.\n");
        // Free previously allocated memory for result_matrix
		free(*result_matrix);
        // Free previously allocated memory for B_transpose
		free(*B_transpose); 
        // Exit program with failure status
		exit(EXIT_FAILURE);
    }

	// Allocate memory for A_square_x_B
    *A_square_x_B = malloc(N * N * sizeof(double)); // Allocate memory for A_square_x_B
	// Check if allocation was successful
    if (*A_square_x_B == NULL) {
        // printf("Error: failed to allocate memory for A_square_x_B.\n");
        // Free previously allocated memory for result_matrix
		free(*result_matrix);
        // Free previously allocated memory for B_transpose
		free(*B_transpose); 
		 // Free previously allocated memory for A_square
        free(*A_square);
        // Exit program with failure status
		exit(EXIT_FAILURE);
    }
}

/* This function deallocates memory for three matrices: B_transpose, A_square, and A_square_x_B.
It takes in three pointers to the matrices. */
void dealloc_matrix(double *B_transpose, double *A_square, double *A_square_x_B) {
    free(B_transpose); // Deallocate memory for B_transpose
    free(A_square); // Deallocate memory for A_square
    free(A_square_x_B); // Deallocate memory for A_square_x_B
}

/* This function computes the transpose of a square matrix B of size N x N
and stores the result in B_transpose, another N x N matrix.
It takes in the integer N, which specifies the dimensions of the matrices,
as well as pointers to the matrices B and B_transpose. */
void compute_transpose(int N, double *B, double *B_transpose) {
	int i, j;
    /* Iterate through the rows and columns of the matrices B and B_transpose */
    for (i = 0; i < N; ++i) {
        for (j = 0; j < N; ++j) {
            /* Compute the transpose of B by swapping its
			rows and columns and store it in B_transpose */
            B_transpose[i * N + j] = B[j * N + i];
        }
    }
}

/* This function computes the square of a square matrix A of size N x N and
stores the result in A_square, another N x N matrix.
It takes in the integer N, which specifies the dimensions of the matrices,
as well as pointers to the matrices A and A_square. */
void compute_square(int N, double *A, double *A_square) {
	int i, j, k;
    /* Iterate through the rows and columns of the matrices A and A_square */
    for (i = 0; i < N; ++i) {
        for (j = 0; j < N; ++j) {
            /* Initialize the current element of A_square to 0 */
            A_square[i * N + j] = 0;
            /* Compute the square of A by multiplying its rows and
			columns and store it in A_square */
            for (k = 0; k < N; ++k) {
                A_square[i * N + j] += A[i * N + k] * A[k * N + j];
            }
        }
    }
}

/* This function computes the product of two square matrices, A_square and B, of
size N x N and stores the result in A_square_x_B, another N x N matrix.
It takes in the integer N, which specifies the dimensions of the matrices,
as well as pointers to the matrices A_square, B, and A_square_x_B. */
void compute_product(int N, double *A_square, double *B, double *A_square_x_B) {
	int i, j, k;
    /* Iterate through the rows and columns of the matrices A_square and B */
    for (i = 0; i < N; ++i) {
        for (j = 0; j < N; ++j) {
            /* Initialize the current element of A_square_x_B to 0 */
            A_square_x_B[i * N + j] = 0;
            /* Compute the product of A_square and B by multiplying their rows
			and columns and store it in A_square_x_B */
            for (k = 0; k < N; ++k) {
                A_square_x_B[i * N + j] += A_square[i * N + k] * B[k * N + j];
            }
        }
    }
}

/* This function computes the element-wise sum of two square matrices, A and B,
of size N x N and stores the result in C, another N x N matrix.
It takes in the integer N, which specifies the dimensions of the matrices, as
well as pointers to the matrices A, B, and C. */
void compute_sum(int N, double *A, double *B, double *C) {
	int i, j;
    /* Iterate through the rows and columns of the matrices A and B */
    for (i = 0; i < N; ++i) {
        for (j = 0; j < N; ++j) {
            /* Compute the sum of the corresponding elements of A and B
			and store it in C */
            C[i * N + j] = A[i * N + j] + B[i * N + j];
        }
    }
}