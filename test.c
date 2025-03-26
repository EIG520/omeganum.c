#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <math.h>

#include "omeganum.c"
#include "notations/raw_array.c"
#include "test.h"

int main() {
    test_zero();
    test_from_double();
    test_abs();
    test_from_raw();
}

// More a test of normalize than of from_double
void test_from_double() {
    FILE *file = fopen(FROM_DOUBLE_TEST_PATH, "r");

    char buf[BUFSIZ];
    int cases = 0;

    while (!feof(file)) {
        fgets(buf, BUFSIZ, file);
        double testcase = strtod(buf, NULL);
        Big num_omeganum = omeganum_from_double(testcase);
        double omeganum_value = omeganum_to_double(&num_omeganum);

        assert(num_omeganum.array_size >= 1);
        assert(num_omeganum.max_array_size >= num_omeganum.array_size);

        assert(approx_eq(testcase, omeganum_value));

        omeganum_free(&num_omeganum);
        cases ++;
    }

    fclose(file);

    printf("Passed %i test cases from %s (from_double)", cases, FROM_DOUBLE_TEST_PATH);
    printf("\n");
}

void test_from_raw() {
    FILE *in_file = fopen(FROM_RAW_TEST_PATH, "r");
    FILE *expected_file = fopen(FROM_RAW_EXPECTED_PATH, "r");

    char testcase[BUFSIZ];
    char expected[BUFSIZ];
    char* str;
    int cases = 0;

    while (!feof(in_file) & !feof(expected_file)) {
        fgets(testcase, BUFSIZ, in_file);
        fgets(expected, BUFSIZ, expected_file);

        expected[strcspn(expected, "\n")] = 0;

        Big num_omeganum = omeganum_from_string(testcase);
        char* value = omeganum_to_string(num_omeganum);

        assert(strcmp(expected, value) == 0);
        cases ++;

        free(value);
        omeganum_free(&num_omeganum);
    }

    fclose(in_file);
    fclose(expected_file);

    printf("Passed %i test cases from %s (from_raw)\n", cases, FROM_RAW_TEST_PATH);
}

void test_abs() {
    FILE *file = fopen(ABS_TEST_PATH, "r");

    char buf[BUFSIZ];
    int cases = 0;

    while (!feof(file)) {
        fgets(buf, BUFSIZ, file);
        double testcase = strtod(buf, NULL);
        double expected = fabs(testcase);

        Big num_omeganum = omeganum_from_double(testcase);
        Big num_omeganum_abs = omeganum_abs(&num_omeganum);
        double omeganum_value = omeganum_to_double(&num_omeganum_abs);
        
        assert(approx_eq(expected, omeganum_value));
        cases ++;

        omeganum_free(&num_omeganum);
        omeganum_free(&num_omeganum_abs);
    }

    fclose(file);

    printf("Passed %i test cases from %s (abs)\n", cases, ABS_TEST_PATH);
}

bool approx_eq(double target, double value) {
    char truncated_target[REQUIRED_PRECISION], truncated_value[REQUIRED_PRECISION];
    snprintf(truncated_target, REQUIRED_PRECISION, "%f", target);
    snprintf(truncated_value, REQUIRED_PRECISION, "%f", value);

    // printf("Expected: %s... Received: %s...\n", truncated_target, truncated_value);

    return strcmp(truncated_target, truncated_value) == 0;
}

// Sanity check
void test_zero() {
    Big zero = omeganum_zero();
    for (size_t i = 0; i < zero.array_size; i++) { assert(zero.array[i] == 0); }

    printf("Passed zero test\n");

    omeganum_free(&zero);
}

