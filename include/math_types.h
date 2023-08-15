#ifndef NUMERICALMATH_MATH_TYPES_H
#define NUMERICALMATH_MATH_TYPES_H

#include <stdint.h>
#include <stdbool.h>

typedef float float32_t;
typedef double float64_t;


typedef enum{
    MATH_SUCCESS,
    MATH_ERROR,
    MATH_WRONG_MATRIX_DIMENSIONS
} status;

typedef struct{
    uint16_t num_cols;
    uint16_t num_rows;
    float* p_data;
} matrix_f32;

#endif //NUMERICALMATH_MATH_TYPES_H
