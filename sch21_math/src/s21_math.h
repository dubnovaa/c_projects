#ifndef SRC_MATH_H_

#define SRC_MATH_H_
#define pi 3.141592653589793
#define S21_EPS 1e-17
#define epsilon 10e-12
#define sqrt3 1.73205080756887729352744
#define pi_6 0.52359877559829887307710723
#define pi_2 1.57079632679489661923132169

int s21_abs(int x);
long double s21_acos(double x);
long double s21_asin(double x);
long double s21_atan(double x);
long double s21_ceil(double x);
long double s21_cos(double x);
long double s21_exp(double x);
long double s21_fabs(double x);
long double s21_floor(double x);
long double s21_fmod(double x, double y);
long double s21_log(double x);
long double s21_pow(double base, double exp);
long double s21_sin(double x);
long double s21_sqrt(double x);
long double s21_tan(double x);
double use_periodicity(double x);
double use_periodicity_tan(double x);
double use_symmetry_sin(double x, int* flag);
double use_symmetry_cos(double x, int* flag);
int close_on_angle(double x);
#endif  // !SRC_MATH_H_