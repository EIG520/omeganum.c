#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>
#include "omeganum.h"

Big omeganum_zero() {
    return omeganum_from_double(0.0);
}

Big omeganum_from_double(double num_ieee) {
    Big num_omeganum;
    num_omeganum.array = (double*)calloc(1, sizeof(double)); 
    num_omeganum.array[0] = fabs(num_ieee);
    num_omeganum.array_size = num_omeganum.max_array_size = 1;
    num_omeganum.sign = (0 < num_ieee) - (num_ieee < 0);
    
    return *omeganum_normalize_(&num_omeganum);
}

Big omeganum_from_parts(double* array, size_t len, int sign) {
    Big num_omeganum;
    num_omeganum.array = array;
    num_omeganum.array_size = len;
    num_omeganum.max_array_size = len;
    num_omeganum.sign = sign;

    return *omeganum_normalize_(&num_omeganum);
}

double omeganum_to_double(Big* num) {
    if (num->array_size >= 2 && (num->array[1] >= 2 || num->array[0] >= MAX_FLOAT_E)) {return INFINITY * num->sign;}
    if (num->array[1] == 1) {return pow(10, num->array[0]) * num->sign;}
    return num->array[0] * num->sign;
}

void omeganum_free(Big* num) {
    free(num->array);
}

Big omeganum_clone(Big* num) {
    Big cloned;
    cloned.sign = num->sign;
    cloned.array = (double*)calloc(num->max_array_size, sizeof(double));
    memcpy(cloned.array, num->array, num->array_size * sizeof(double));
    cloned.array_size = num->array_size;
    cloned.max_array_size = num->max_array_size;

    return cloned;
}

Big omeganum_abs(Big* num) {
    Big cloned = omeganum_clone(num);
    return *omeganum_abs_(&cloned);
}

Big* omeganum_abs_(Big* num) {
    num->sign = num->sign * num->sign;
    return num;
}

Big omeganum_negate(Big* num) {
    Big cloned = omeganum_clone(num);
    return *omeganum_negate_(&cloned);
}

Big* omeganum_negate_(Big* num) {
    num->sign *= -1;
    return num;
}

int omeganum_cmp(Big* num1, Big* num2) {
    if (isnan(num1->array[0]) || isnan(num2->array[0])) {return NAN_INT;}
    if (num1->array[0] == INFINITY && num2->array[0] != INFINITY) {return num1->sign;}
    if (num2->array[0] == INFINITY && num1->array[0] != INFINITY) {return -num2->sign;}
    if (num1->array_size == 1 && num2->array_size == 1 && num1->array[0] == 0 && num2->array[0] ==0) {return 0;}
    if (num1->sign != num2->sign) {return num1->sign;}
    if (num1->array_size > num2->array_size) {return num1->sign;}
    if (num1->array_size < num2->array_size) {return -num1->sign;}

    for (int i = num1->array_size - 1; i >= 0; i--) {
        if (num1->array[i] > num2->array[i]) {return num1->sign;}
        if (num2->array[i] > num1->array[i]) {return -num1->sign;}
    }

    return 0;
}

Big omeganum_normalize(Big* num) {
    Big cloned = omeganum_clone(num);
    return *omeganum_normalize_(&cloned);
}

Big* omeganum_normalize_(Big* num) {
    while (num->array_size > 1 && num->array[num->array_size - 1] == 0) { num->array_size -= 1; }

    for (size_t i = 0; i < num->array_size; i++) {
        if (!isfinite(num->array[i])) {
            double invalid_entry = num->array[i];
            free(num->array);
            num->array = calloc(1, sizeof(double));
            num->array[0] = invalid_entry;
            num->array_size = num->max_array_size = 1;
            return num;
        }
    }

    bool run_again = true;
    while (run_again) {
        run_again = false;

        while (num->array_size > 1 && num->array[num->array_size - 1] == 0) { num->array_size -= 1; }

        while (num->array[0] > MAX_SAFE_INTEGER) {
            if (num->array_size < 2) {omeganum_expand_array_once(num);}
            num->array[0] = log10(num->array[0]);
            num->array[1] ++;

            run_again = true;
        }

        while (num->array[0] < MAX_E && num->array_size >= 2 && num->array[1] > 0) {
            num->array[0] = pow(10, num->array[0]);
            num->array[1] --;

            run_again = true;
        }

        if (num->array_size > 2 && num->array[1] == 0) {
            int i = 0;
            while (num->array[i] == 0) {i++;}
            
            num->array[i-1] = num->array[0];
            num->array[i] --;
            num->array[0] = 1;

            run_again = true;
        }

        for (size_t i = 0; i < num->array_size; i++) {
            if (num->array[i] > MAX_SAFE_INTEGER) {
                if (num->array_size <= i+1) {omeganum_expand_array_once(num);}

                num->array[i+1] ++;
                num->array[0] = num->array[i] + 1;
                memset(num->array+1, 0, i * sizeof(double));

                run_again = true;
            }
        }
    }

    return num;
}

void omeganum_expand_array_once(Big* num) {
    num->array_size += 1;
    if (num->max_array_size < num->array_size) { omeganum_reserve_step(num); }
    else {num->array[num->array_size-1] = 0;}
}

void omeganum_reserve_step(Big* num) {
    double* array = (double*)calloc(2 * num->max_array_size, sizeof(double));
    memcpy(array, num->array, num->array_size * sizeof(double));
    free(num->array);
    num->max_array_size = 2 * num->max_array_size;
    num->array = array;
}