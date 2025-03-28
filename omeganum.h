#include <stdlib.h>
#include <math.h>
#include <float.h>

#ifndef OMEGANUM_H
#define OMEGANUM_H

#define NAN_INT 42 
#define MAX_SAFE_INTEGER 9007199254740992
#define MAX_E log10(MAX_SAFE_INTEGER)
#define MAX_FLOAT_E log10(DBL_MAX)

typedef struct {
    int sign;
    double* array;
    size_t array_size;
    size_t max_array_size;
} Big;

// Create a bignum
Big omeganum_e_max();
Big omeganum_ee_max();
Big omeganum_from_double(double num_ieee);
Big omeganum_from_parts(double* array, size_t len, int sign);

// Functions ending with _ will return a pointer to the result and may modify the args

Big omeganum_clone(Big* num);
Big omeganum_abs(Big* num);
Big* omeganum_abs_(Big* num);
Big omeganum_negate(Big* num);
Big* omeganum_negate_(Big* num);
Big omeganum_normalize(Big* num);
Big* omeganum_normalize_(Big* num);
Big omeganum_add(Big* num, Big* other);
Big* omeganum_add_(Big* num, Big* other);

double omeganum_to_double(Big* num);

int omeganum_cmp(Big* num1, Big* num2);
int omeganum_gt(Big* num1, Big* num2) { return omeganum_cmp(num1, num2) > 0; }
int omeganum_lt(Big* num1, Big* num2) { return omeganum_cmp(num1, num2) < 0; }
int omeganum_gte(Big* num1, Big* num2) { return omeganum_cmp(num1, num2) >= 0; }
int omeganum_lte(Big* num1, Big* num2) { return omeganum_cmp(num1, num2) <= 0; }
int omeganum_eq(Big* num1, Big* num2) { return omeganum_cmp(num1, num2) == 0; }
int omeganum_neq(Big* num1, Big* num2) { return omeganum_cmp(num1, num2) != 0; }
Big* omeganum_max(Big* num1, Big* num2) { if (omeganum_gt(num1, num2)) { return num1; } else { return num2; } };
Big* omeganum_min(Big* num1, Big* num2) { if (omeganum_gt(num1, num2)) { return num2; } else { return num1; } };

void omeganum_free(Big* num);
void omeganum_expand_array_once(Big* num);
void omeganum_reserve_step(Big* num);

#endif