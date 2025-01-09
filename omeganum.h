#include <stdlib.h>
#include <math.h>
#include <float.h>

#ifndef OMEGANUM_H
#define OMEGANUM_H

#define MAX_SAFE_INTEGER 9007199254740992
#define MAX_E log10(MAX_SAFE_INTEGER)
#define MAX_FLOAT_E log10(DBL_MAX)

typedef struct {
    int sign;
    double* array;
    size_t array_size;
    size_t max_array_size;
} Big;

Big omeganum_zero();
Big omeganum_from_double(double num_ieee);
Big omeganum_clone(Big* num);
Big omeganum_abs(Big* num);
Big omeganum_negate(Big* num);

int omeganum_cmp(Big* num1, Big* num2);
double omeganum_to_double(Big* num);

int omeganum_gt(Big* num1, Big* num2) { return omeganum_cmp(num1, num2) > 0; }
int omeganum_lt(Big* num1, Big* num2) { return omeganum_cmp(num1, num2) < 0; }
int omeganum_gte(Big* num1, Big* num2) { return omeganum_cmp(num1, num2) >= 0; }
int omeganum_lte(Big* num1, Big* num2) { return omeganum_cmp(num1, num2) <= 0; }
int omeganum_eq(Big* num1, Big* num2) { return omeganum_cmp(num1, num2) == 0; }
int omeganum_neq(Big* num1, Big* num2) { return omeganum_cmp(num1, num2) != 0; }

void omeganum_free(Big* num);
void omeganum_normalize(Big* num);
void omeganum_expand_array_once(Big* num);
void omeganum_reserve_step(Big* num);

#endif