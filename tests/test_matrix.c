#include <stdlib.h>
#include <check.h>
#include "../include/matrix_math.h"

// Unit test for matrix multiplication with identity matrix
START_TEST(test_matrix_multiplication_identity_matrix) {
    matrix_f32 mat1, mat2, result;

    // Initialize matrices
    float32_t data1[] = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f};
    matrix_init_f32(&mat1, 2, 3, data1);

    float32_t data2[] = {1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f};
    matrix_init_f32(&mat2, 3, 2, data2);

    float32_t data3[9];
    matrix_init_f32(&result, 3, 3, data3);

    // Perform matrix multiplication
    status s = matrix_mul_f32(&mat1, &mat2, &result);

    // Check the status of matrix multiplication (should be MATH_SUCCESS)
    ck_assert_int_eq(s, MATH_SUCCESS);

    // The result should be equal to mat1 since mat2 is an identity matrix
    float32_t expected_data[] = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f};
    matrix_f32 expected_result;
    matrix_init_f32(&expected_result, 2, 2, expected_data);
    ck_assert_int_eq(matrix_is_equal_f32(&result, &expected_result, 1e-6), 1);
}
END_TEST

// Unit test for matrix multiplication with zero matrix
START_TEST(test_matrix_multiplication_zero_matrix) {
    matrix_f32 mat1, mat2, result;

    // Initialize matrices
    float32_t data1[] = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f};
    matrix_init_f32(&mat1, 2, 3, data1);

    float32_t data2[] = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};
    matrix_init_f32(&mat2, 3, 2, data2);

    float32_t data3[4];
    matrix_init_f32(&result, 3, 3, data3);

    // Perform matrix multiplication
    status s = matrix_mul_f32(&mat1, &mat2, &result);

    // Check the status of matrix multiplication (should be MATH_SUCCESS)
    ck_assert_int_eq(s, MATH_SUCCESS);

    // The result should be a zero matrix since mat2 is a zero matrix
    float32_t expected_data[] = {0.0f, 0.0f, 0.0f, 0.0f};
    matrix_f32 expected_result;
    matrix_init_f32(&expected_result, 2, 2, expected_data);
    ck_assert_int_eq(matrix_is_equal_f32(&result, &expected_result, 1e-6), 1);
}
END_TEST

// Unit test for matrix multiplication with non-square matrices
START_TEST(test_matrix_multiplication_non_square) {
    matrix_f32 mat1, mat2, result;

    // Initialize matrices
    float32_t data1[] = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f};
    matrix_init_f32(&mat1, 2, 3, data1);

    float32_t data2[] = {1.0f, 2.0f, 3.0f, 4.0f};
    matrix_init_f32(&mat2, 2, 2, data2);

    float32_t data3[4];
    matrix_init_f32(&result, 2, 2, data3);

    // Perform matrix multiplication
    status s = matrix_mul_f32(&mat1, &mat2, &result);

    // Check the status of matrix multiplication (should be STATUS_ERROR_DIMENSIONS_MISMATCH)
    ck_assert_int_eq(s, MATH_WRONG_MATRIX_DIMENSIONS);
}
END_TEST

// Unit test for matrix multiplication with matrices having elements with decimal values
START_TEST(test_matrix_multiplication_decimal_values) {
    matrix_f32 mat1, mat2, result;

    // Initialize matrices with decimal values
    float32_t data1[] = {0.1f, 0.2f, 0.3f, 0.4f, 0.5f, 0.6f};
    matrix_init_f32(&mat1, 2, 3, data1);

    float32_t data2[] = {0.7f, 0.8f, 0.9f, 1.0f, 1.1f, 1.2f};
    matrix_init_f32(&mat2, 3, 2, data2);

    float32_t data3[9];
    matrix_init_f32(&result, 3, 3, data3);

    // Perform matrix multiplication
    status s = matrix_mul_f32(&mat1, &mat2, &result);

    // Check the status of matrix multiplication (should be MATH_SUCCESS)
    ck_assert_int_eq(s, MATH_SUCCESS);

    // The expected result (manually calculated)
    float32_t expected_data[] = {
            0.2700f,    0.3000f,   0.3300f,
            0.6100f,    0.6800f,   0.7500f,
            0.9500f,    1.0600f,   1.1700f,
    };
    matrix_f32 expected_result;
    matrix_init_f32(&expected_result, 2, 2, expected_data);
    ck_assert_int_eq(matrix_is_equal_f32(&result, &expected_result, 1e-6), 1);
}
END_TEST

// Unit test for matrix multiplication with matrices having large integer values
START_TEST(test_matrix_multiplication_large_values) {
    matrix_f32 mat1, mat2, result;

    // Initialize matrices with large integer values
    float32_t data1[] = {1000000.0f, 2000000.0f, 3000000.0f, 4000000.0f, 5000000.0f, 6000000.0f};
    matrix_init_f32(&mat1, 2, 3, data1);

    float32_t data2[] = {7000000.0f, 8000000.0f, 9000000.0f, 10000000.0f, 11000000.0f, 12000000.0f};
    matrix_init_f32(&mat2, 3, 2, data2);

    // Perform matrix multiplication
    status s = matrix_mul_f32(&mat1, &mat2, &result);

    // Check the status of matrix multiplication (should be MATH_SUCCESS)
    ck_assert_int_eq(s, MATH_SUCCESS);

    // The expected result (manually calculated)
    float32_t expected_data[] = {50000000000000.0f, 56000000000000.0f, 125000000000000.0f, 140000000000000.0f};
    matrix_f32 expected_result;
    matrix_init_f32(&expected_result, 2, 2, expected_data);
    ck_assert_int_eq(matrix_is_equal_f32(&result, &expected_result, 1e-6), 1);
}
END_TEST

// Unit test for matrix multiplication with matrices having negative values
START_TEST(test_matrix_multiplication_negative_values) {
    matrix_f32 mat1, mat2, result;

    // Initialize matrices with negative values
    float32_t data1[] = {-1.0f, -2.0f, -3.0f, -4.0f, -5.0f, -6.0f};
    matrix_init_f32(&mat1, 2, 3, data1);

    float32_t data2[] = {-7.0f, -8.0f, -9.0f, -10.0f, -11.0f, -12.0f};
    matrix_init_f32(&mat2, 3, 2, data2);

    // Perform matrix multiplication
    status s = matrix_mul_f32(&mat1, &mat2, &result);

    // Check the status of matrix multiplication (should be MATH_SUCCESS)
    ck_assert_int_eq(s, MATH_SUCCESS);

    // The expected result (manually calculated)
    float32_t expected_data[] = {58.0f, 64.0f, 139.0f, 154.0f};
    matrix_f32 expected_result;
    matrix_init_f32(&expected_result, 2, 2, expected_data);
    ck_assert_int_eq(matrix_is_equal_f32(&result, &expected_result, 1e-6), 1);
}
END_TEST

// Unit test for matrix multiplication with zero-size matrices (should fail)
START_TEST(test_matrix_multiplication_zero_size_matrices) {
    matrix_f32 mat1, mat2, result;

    // Initialize zero-size matrices
    float32_t data1[] = {};
    matrix_init_f32(&mat1, 0, 0, data1);

    float32_t data2[] = {};
    matrix_init_f32(&mat2, 0, 0, data2);

    // Perform matrix multiplication
    status s = matrix_mul_f32(&mat1, &mat2, &result);

    // Check the status of matrix multiplication (should be STATUS_ERROR_DIMENSIONS_MISMATCH)
    ck_assert_int_eq(s, MATH_WRONG_MATRIX_DIMENSIONS);
}
END_TEST

// Unit test for matrix multiplication with one of the matrices being a row matrix
START_TEST(test_matrix_multiplication_row_matrix) {
    matrix_f32 mat1, mat2, result;

    // Initialize matrices (example data)
    float32_t data1[] = {1.0f, 2.0f, 3.0f};
    matrix_init_f32(&mat1, 1, 3, data1);

    float32_t data2[] = {4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f};
    matrix_init_f32(&mat2, 2, 3, data2);

    // Perform matrix multiplication
    status s = matrix_mul_f32(&mat1, &mat2, &result);

    // Check the status of matrix multiplication (should be MATH_SUCCESS)
    ck_assert_int_eq(s, MATH_SUCCESS);

    // The expected result (manually calculated)
    float32_t expected_data[] = {40.0f, 46.0f, 52.0f};
    matrix_f32 expected_result;
    matrix_init_f32(&expected_result, 1, 3, expected_data);
    ck_assert_int_eq(matrix_is_equal_f32(&result, &expected_result, 1e-6), 1);
}
END_TEST

// Unit test for matrix multiplication with one of the matrices being a column matrix
START_TEST(test_matrix_multiplication_column_matrix) {
    matrix_f32 mat1, mat2, result;

    // Initialize matrices (example data)
    float32_t data1[] = {1.0f, 2.0f, 3.0f};
    matrix_init_f32(&mat1, 3, 1, data1);

    float32_t data2[] = {4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f};
    matrix_init_f32(&mat2, 2, 3, data2);

    // Perform matrix multiplication
    status s = matrix_mul_f32(&mat1, &mat2, &result);

    // Check the status of matrix multiplication (should be MATH_SUCCESS)
    ck_assert_int_eq(s, MATH_SUCCESS);

    // The expected result (manually calculated)
    float32_t expected_data[] = {40.0f, 46.0f};
    matrix_f32 expected_result;
    matrix_init_f32(&expected_result, 3, 1, expected_data);
    ck_assert_int_eq(matrix_is_equal_f32(&result, &expected_result, 1e-6), 1);
}
END_TEST

// Unit test for matrix multiplication with both matrices being 1x1 (scalar multiplication)
START_TEST(test_matrix_multiplication_scalar) {
    matrix_f32 mat1, mat2, result;

    // Initialize matrices (scalar values)
    float32_t data1[] = {5.0f};
    matrix_init_f32(&mat1, 1, 1, data1);

    float32_t data2[] = {7.0f};
    matrix_init_f32(&mat2, 1, 1, data2);

    // Perform matrix multiplication
    status s = matrix_mul_f32(&mat1, &mat2, &result);

    // Check the status of matrix multiplication (should be MATH_SUCCESS)
    ck_assert_int_eq(s, MATH_SUCCESS);

    // The expected result (manually calculated)
    float32_t expected_data[] = {35.0f};
    matrix_f32 expected_result;
    matrix_init_f32(&expected_result, 1, 1, expected_data);
    ck_assert_int_eq(matrix_is_equal_f32(&result, &expected_result, 1e-6), 1);
}
END_TEST

// ... (write more tests based on different scenarios and edge cases)

// Function to set up the test suite
Suite* matrix_math_suite(void) {
    Suite* suite = suite_create("Matrix Math");

    TCase* tcase_identity = tcase_create("Matrix Multiplication with Identity Matrix");
    tcase_add_test(tcase_identity, test_matrix_multiplication_identity_matrix);
    suite_add_tcase(suite, tcase_identity);

    TCase* tcase_zero = tcase_create("Matrix Multiplication with Zero Matrix");
    tcase_add_test(tcase_zero, test_matrix_multiplication_zero_matrix);
    suite_add_tcase(suite, tcase_zero);

    TCase* tcase_non_square = tcase_create("Matrix Multiplication with Non-Square Matrices");
    tcase_add_test(tcase_non_square, test_matrix_multiplication_non_square);
    suite_add_tcase(suite, tcase_non_square);

    TCase* tcase_decimal = tcase_create("Matrix Multiplication with Decimal Values");
    tcase_add_test(tcase_decimal, test_matrix_multiplication_decimal_values);
    suite_add_tcase(suite, tcase_decimal);

    /*TCase* tcase_large_values = tcase_create("Matrix Multiplication with Large Values");
    tcase_add_test(tcase_large_values, test_matrix_multiplication_large_values);
    suite_add_tcase(suite, tcase_large_values);

    TCase* tcase_negative = tcase_create("Matrix Multiplication with Negative Values");
    tcase_add_test(tcase_negative, test_matrix_multiplication_negative_values);
    suite_add_tcase(suite, tcase_negative);

    TCase* tcase_zero_size = tcase_create("Matrix Multiplication with Zero-Size Matrices");
    tcase_add_test(tcase_zero_size, test_matrix_multiplication_zero_size_matrices);
    suite_add_tcase(suite, tcase_zero_size);

    TCase* tcase_row = tcase_create("Matrix Multiplication with Row Matrix");
    tcase_add_test(tcase_row, test_matrix_multiplication_row_matrix);
    suite_add_tcase(suite, tcase_row);

    TCase* tcase_column = tcase_create("Matrix Multiplication with Column Matrix");
    tcase_add_test(tcase_column, test_matrix_multiplication_column_matrix);
    suite_add_tcase(suite, tcase_column);

    TCase* tcase_scalar = tcase_create("Matrix Multiplication with Scalar");
    tcase_add_test(tcase_scalar, test_matrix_multiplication_scalar);
    suite_add_tcase(suite, tcase_scalar);*/

    // Add more test cases here

    return suite;
}


int main(void) {
    int num_failed;
    Suite* suite = matrix_math_suite();
    SRunner* srunner = srunner_create(suite);
    srunner_run_all(srunner, CK_VERBOSE);
    num_failed = srunner_ntests_failed(srunner);
    srunner_free(srunner);
    return (num_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
