#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <math.h>

#include "omeganum.c"
#include "notations/standard.c"
#include "test.h"

int main() {
    test_zero();
    test_from_double();
}

// More a test of normalize than of from_double
void test_from_double() {
    FILE *file = fopen(FROM_DOUBLE_TEST_PATH, "r");

    char buf[BUFSIZ];
    int cases = 0;

    while (!feof(file)) {
        fgets(buf, BUFSIZ, file);
        char** _;
        double testcase = strtod(buf, _);
        Big num_omeganum = omeganum_from_double(testcase);

        double omeganum_value = num_omeganum.array[0];

        assert(num_omeganum.array_size >= 1);
        assert(num_omeganum.max_array_size >= num_omeganum.array_size);

        if (num_omeganum.array_size > 1) {
            double exp_iters = num_omeganum.array[1];
            for (double i = exp_iters; i > 0; i--) { omeganum_value = pow(10, omeganum_value); }
        }

        omeganum_value *= num_omeganum.sign;

        char truncated_target[REQUIRED_PRECISION], truncated_value[REQUIRED_PRECISION];
        snprintf(truncated_target, REQUIRED_PRECISION, "%f", testcase);
        snprintf(truncated_value, REQUIRED_PRECISION, "%f", omeganum_value);

        // printf("Expected: %s... Recieved: %s...\n", truncated_target, truncated_value);

        assert(memcmp(truncated_target, truncated_value, REQUIRED_PRECISION) == 0);

        cases ++;
    }

    printf("Passed %i test cases from %s", cases, FROM_DOUBLE_TEST_PATH);
    printf("\n");
}

// Sanity check
void test_zero() {
    Big zero = omeganum_zero();
    for (int i = 0; i < zero.array_size; i++) { assert(zero.array[i] == 0); }

    printf("Passed zero test\n");
}

