#include "s21_matrix.h"

void generate_matrix(matrix_t *A, double lambda) {
  // printf("%d\t", A->rows);
  // printf("%d\t", A->columns);
  for (int i = 0; i < A->rows; i++) {
    // printf("%d\t", i);
    for (int j = 0; j < A->columns; j++) {
      if ((i == A->rows - 1) && (j == A->columns - 1))
        A->matrix[i][j] = lambda * i + j + lambda;
      else
        A->matrix[i][j] = lambda * (i + j);
    }
  }
}

void print_matrix(matrix_t *A) {
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      if (j != A->columns - 1)
        printf("%f ", A->matrix[i][j]);
      else
        printf("%f", A->matrix[i][j]);
    }
    printf("\n");
  }
}