#ifndef NUMERICALMATH_UTILITIES_H
#define NUMERICALMATH_UTILITIES_H

#include "math_types.h"
#include <math.h>

uint16_t MAX_COL(matrix_f32* matrix, uint16_t start_row, uint16_t column);
void SWAP_ROWS(matrix_f32* matrix, uint16_t row_a, uint16_t row_b);
void INVERSE_TRIANGULAR(matrix_f32* src, matrix_f32* inv, uint8_t upper);

#endif //NUMERICALMATH_UTILITIES_H
