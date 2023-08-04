#ifndef LEARNINGC_MATRIX_MATH_H
#define LEARNINGC_MATRIX_MATH_H

#include <math.h>
#include "math_types.h"
#include "utilities.h"

// Initialization functions
void matrix_init_f32(matrix_f32* mat, uint16_t num_cols, uint16_t num_rows, float32_t* p_data);
bool matrix_is_equal_f32(matrix_f32* a, matrix_f32* b, float32_t tolerance);

// Math functions
status lu_decomposition_f32(matrix_f32* src, matrix_f32* lt, matrix_f32* ut, matrix_f32* p);
status inverse_matrix_f32(matrix_f32* src, matrix_f32* dst);
status matrix_mul_f32(matrix_f32* a, matrix_f32* b, matrix_f32* dst);
status matrix_add_f32(matrix_f32* a, matrix_f32* b, matrix_f32* dst);
status matrix_sub_f32(matrix_f32* a, matrix_f32* b, matrix_f32* dst);

#endif //LEARNINGC_MATRIX_MATH_H
