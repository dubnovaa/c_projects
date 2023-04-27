#include "s21_matrix.h"

int s21_check_two_matrices(matrix_t *A, matrix_t *B, int full_eq) {
  int res = OK;
  if (!A || !B || !(A->matrix) || !(B->matrix))
    res = ERR;
  else if (A->columns <= 0 || A->rows <= 0 || B->columns <= 0 || B->rows <= 0)
    res = ERR;
  else if (full_eq) {
    if ((A->rows != B->rows) || (A->columns != B->columns)) res = CALC;
  } else if (A->columns != B->rows)
    res = CALC;  // multiplication
  return res;
}

int s21_check_one_matrix(matrix_t *A) {
  int res = OK;
  // printf("\nrows %d columns %d\n", A->rows, A->columns);
  if (!A || !(A->matrix) || A->columns <= 0 || A->rows <= 0) res = ERR;
  return res;
}

void s21_matrix_minor(matrix_t *src, matrix_t *dst, int row_del, int col_del) {
  for (int src_row = 0, dst_row = 0; src_row < src->rows;
       src_row++, dst_row++) {
    // int src_col = 0, dst_col = 0;
    if (src_row == row_del) src_row++;
    for (int src_col = 0, dst_col = 0;
         src_col < src->columns && src_row < src->rows; src_col++, dst_col++) {
      if (src_col == col_del) src_col++;
      if (src_col < src->columns)
        dst->matrix[dst_row][dst_col] = src->matrix[src_row][src_col];
    }
  }
}
