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
    omeganum_normalize(&num_omeganum);

    return num_omeganum;
}

void omeganum_free(Big num) {
    free(num.array);
}

void omeganum_normalize(Big* num) {
    while (num->array_size > 1 && num->array[num->array_size - 1] == 0) { num->array_size -= 1; }

    for (int i = 0; i < num->array_size; i++) {
        if (!isfinite(num->array[i])) {
            double invalid_entry = num->array[i];
            free(num->array);
            num->array = calloc(1, sizeof(double));
            num->array[0] = invalid_entry;
            num->array_size = num->max_array_size = 1;
            return;
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

        while (num->array[0] < MAX_E && num->array_size > 2 && num->array[1] > 0) {
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

        for (int i = 0; i < num->array_size; i++) {
            if (num->array[i] > MAX_SAFE_INTEGER) {
                if (num->array_size < i+1) {omeganum_expand_array_once(num);}

                num->array[i+1] ++;
                num->array[0] = num->array[i] + 1;
                memset(num->array+1, 0, i * sizeof(double));

                run_again = true;
            }
        }
    }
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