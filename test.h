#ifndef TEST_H
#define TEST_H

#define FROM_DOUBLE_TEST_PATH "tests/doubles.txt"
#define ABS_TEST_PATH "tests/doubles.txt"

#define FROM_RAW_TEST_PATH "tests/raw_array.txt"
#define FROM_RAW_EXPECTED_PATH "tests/raw_array_expected.txt"

#define REQUIRED_PRECISION 10

void test_zero();
void test_from_double();
void test_abs();
void test_from_raw();

bool approx_eq(double target, double value);

#endif
