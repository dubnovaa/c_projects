#include "s21_matrix.h"

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int res = OK;
  if (rows <= 0 || columns <= 0 || !result) {
    res = ERR;
  } else {
    result->rows = rows;
    result->columns = columns;
    result->matrix = (double **)calloc(rows * columns + rows, sizeof(double *));
    double *ptr = (double *)(result->matrix + rows);
    for (int i = 0; i < rows; i++) {
      result->matrix[i] = ptr + columns * i;
    }
    if (!result->matrix) res = ERR;
  }
  return res;
}

void s21_remove_matrix(matrix_t *A) {
  if (A->matrix) free(A->matrix);
  A->matrix = NULL;
  A->rows = 0;
  A->columns = 0;
}

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int res = s21_check_two_matrices(A, B, 1);
  res = (res == OK) ? SUCCESS : FAILURE;
  if (res == SUCCESS) {
    for (int i = 0; i < A->rows && res; i++) {
      for (int j = 0; j < A->columns && res; j++) {
        double diff = (A->matrix[i][j] - B->matrix[i][j]) > 0
                          ? (A->matrix[i][j] - B->matrix[i][j])
                          : -(A->matrix[i][j] - B->matrix[i][j]);
        if (diff > EPS) res = FAILURE;
      }
    }
  }
  return res;
}

void simple_arythm_matrix(matrix_t *A, matrix_t *B, matrix_t *result, int sum) {
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      if (sum)
        result->matrix[i][j] = (A->matrix[i][j] + B->matrix[i][j]);
      else
        result->matrix[i][j] = (A->matrix[i][j] - B->matrix[i][j]);
    }
  }
}

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int res = s21_check_two_matrices(A, B, 1);
  if (!result) res = ERR;
  if (res == OK) res = s21_create_matrix(A->rows, A->columns, result);
  if (res == OK) simple_arythm_matrix(A, B, result, 1);
  return res;
}

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int res = s21_check_two_matrices(A, B, 1);
  if (!result) res = ERR;
  if (res == OK) res = s21_create_matrix(A->rows, A->columns, result);
  if (res == OK) simple_arythm_matrix(A, B, result, 0);
  return res;
}

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  int res = s21_check_one_matrix(A);
  if (res == OK && (!result || !number)) res = ERR;
  if (res == OK) res = s21_create_matrix(A->rows, A->columns, result);
  if (res == OK) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[i][j] = number * A->matrix[i][j];
      }
    }
  }
  return res;
}

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int res = s21_check_two_matrices(A, B, 0);
  if (!result) res = ERR;
  if (res == OK) res = s21_create_matrix(A->rows, B->columns, result);
  if (res == OK) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < B->columns; j++) {
        result->matrix[i][j] = 0;
        for (int k = 0; k < B->rows; k++) {
          result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
        }
      }
    }
  }
  return res;
}

int s21_transpose(matrix_t *A, matrix_t *result) {
  int res = s21_check_one_matrix(A);
  if (!result) res = ERR;
  if (res == OK) res = s21_create_matrix(A->columns, A->rows, result);
  if (res == OK) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[j][i] = A->matrix[i][j];
      }
    }
  }
  return res;
}
int s21_calc_complements(matrix_t *A, matrix_t *result) {
  int res = s21_check_one_matrix(A);
  if (!result) res = ERR;
  if (res == OK && A->columns != A->rows) res = CALC;
  if (res == OK) res = s21_create_matrix(A->rows, A->columns, result);
  if (res == OK) {
    if (A->rows == 1)
      result->matrix[0][0] = A->matrix[0][0];
    else {
      for (int row = 0; row < A->rows; row++) {
        for (int col = 0; col < A->columns; col++) {
          matrix_t minor;
          s21_create_matrix(A->rows - 1, A->columns - 1, &minor);
          s21_matrix_minor(A, &minor, row, col);
          result->matrix[row][col] =
              calc_det_recursive(&minor) * pow(-1, (row + col));
          s21_remove_matrix(&minor);
        }
      }
    }
  }
  return res;
}

double calc_det_recursive(matrix_t *A) {
  double det_minor = 0;
  if (A->rows == 1)
    det_minor = A->matrix[0][0];
  else if (A->rows == 2)
    det_minor =
        A->matrix[0][0] * A->matrix[1][1] - A->matrix[0][1] * A->matrix[1][0];
  else {
    int sign = 1;
    for (int i = 0; i < A->rows; i++) {
      matrix_t subM;
      s21_create_matrix(A->rows - 1, A->columns - 1, &subM);
      // printf("\nsign %d\n", sign);
      s21_matrix_minor(A, &subM, 0, i);

      det_minor += A->matrix[0][i] * sign * calc_det_recursive(&subM);
      sign = -sign;
      s21_remove_matrix(&subM);
    }
  }
  return det_minor;
}

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  double det;
  int res = s21_check_one_matrix(A);
  if (!result) res = ERR;
  if (res == OK && A->columns != A->rows) res = CALC;
  if (res == OK) {
    det = calc_det_recursive(A);
    if (fabs(det) < EPS) res = CALC;
  }
  if (res == OK) {
    matrix_t minors, minors_T;
    s21_calc_complements(A, &minors);
    s21_transpose(&minors, &minors_T);
    s21_mult_number(&minors_T, 1 / det, result);
    s21_remove_matrix(&minors);
    s21_remove_matrix(&minors_T);
  }
  return res;
}

int s21_determinant(matrix_t *A, double *result) {
  int res = s21_check_one_matrix(A);
  if (!result) res = ERR;
  if (res == OK && A->columns != A->rows) res = CALC;
  if (res == OK) *result = calc_det_recursive(A);
  return res;
}
