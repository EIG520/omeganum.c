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

double omeganum_to_double(Big* num);

void omeganum_free(Big* num);
void omeganum_normalize(Big* num);
void omeganum_expand_array_once(Big* num);
void omeganum_reserve_step(Big* num);

#endif