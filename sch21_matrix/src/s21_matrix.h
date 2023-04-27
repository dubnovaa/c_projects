#ifndef SRC_MATRIX_H_
#define SRC_MATRIX_H_

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#define SUCCESS 1
#define FAILURE 0
#define OK 0
#define ERR 1
#define CALC 2
#define EPS 1e-7
typedef struct matrix_struct {
  double **matrix;
  int rows;
  int columns;
} matrix_t;

int s21_create_matrix(int rows, int columns, matrix_t *result);
void s21_remove_matrix(matrix_t *A);
int s21_eq_matrix(matrix_t *A, matrix_t *B);
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_mult_number(matrix_t *A, double number, matrix_t *result);
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_transpose(matrix_t *A, matrix_t *result);
int s21_calc_complements(matrix_t *A, matrix_t *result);
int s21_determinant(matrix_t *A, double *result);
int s21_inverse_matrix(matrix_t *A, matrix_t *result);

void simple_arythm_matrix(matrix_t *A, matrix_t *B, matrix_t *result, int sum);
void generate_matrix(matrix_t *A, double lambda);
void print_matrix(matrix_t *A);
int s21_check_one_matrix(matrix_t *A);
int s21_check_two_matrices(matrix_t *A, matrix_t *B, int full_eq);
void s21_matrix_minor(matrix_t *src, matrix_t *dst, int row_del, int col_del);
double calc_det_recursive(matrix_t *A);

#endif  // SRC_MATRIX_H_