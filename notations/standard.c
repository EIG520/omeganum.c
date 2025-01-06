#include <stdio.h>

#include "../omeganum.h"

void omeganum_print_raw(Big number) {
    for (int i = number.array_size - 1; i >= 0; i--) {
        printf("%f ", number.array[i]);
    }
}