#include <stdlib.h>
#include <math.h>

#ifndef OMEGANUM_H
#define OMEGANUM_H

#define MAX_SAFE_INTEGER 9007199254740992
#define MAX_E log10(MAX_SAFE_INTEGER)

typedef struct {
    int sign;
    double* array;
    size_t array_size;
    size_t max_array_size;
} Big;

Big omeganum_zero();
Big omeganum_from_double(double num_ieee);

void omeganum_free(Big num);
void omeganum_normalize(Big* num);
void omeganum_expand_array_once(Big* num);
void omeganum_reserve_step(Big* num);

#endif