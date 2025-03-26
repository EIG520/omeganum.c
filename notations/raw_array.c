#include <stdio.h>
#include "../omeganum.h"

// start with - if negative
// follow with space separated list of entries in the array
// that's the entire notation

char* omeganum_to_string(Big number) {
    char* string = calloc(100 * number.array_size, sizeof(char));
    size_t position = 0;
    if (number.sign == -1) { string[position] = '-'; position ++; }

    for (int i = 0; i < number.array_size; i++) {
        if (i > 0) {position += sprintf(string + position, " ");}
        position += sprintf(string + position,"%f", number.array[i]);
    }

    return string;
}

Big omeganum_from_string(char* string) {
    double* omeganum_arr = calloc(1000, sizeof(double));
    int n = 0;
    int i = 0;
    int sign = 1;

    char* ptr = string;

    if (*string == '-') { sign = -1; ptr += 1; }

    for (; *ptr; ptr += n) {
        if (sscanf(ptr, "%lf %n", omeganum_arr + (i++), &n) != 1) {
            break;
        }
    }

    return omeganum_from_parts(omeganum_arr, i, sign);
}