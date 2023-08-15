#include "../include/matrix_math.h"

void matrix_init_f32(matrix_f32* mat, uint16_t num_cols, uint16_t num_rows, float32_t* p_data){
    mat->num_cols = num_cols;
    mat->num_rows = num_rows;
    mat->p_data = p_data;
}

bool matrix_is_equal_f32(matrix_f32* a, matrix_f32* b, float32_t tolerance){
    if(a->num_cols != b->num_cols || a->num_rows != b->num_rows){
        return false;
    }

    uint16_t num_cols = a->num_cols;
    uint16_t num_rows = b->num_rows;
    float32_t diff;

    for(uint16_t i = 0; i < num_rows; i++){
        for(uint16_t j = 0; j < num_cols; j++){
            diff = fabsf(a->p_data[i*num_cols+j] - b->p_data[i*num_cols+j]);
            if(diff > tolerance){
                return false;
            }
        }
    }
    return true;
}

status lu_decomposition_f32(matrix_f32* src, matrix_f32* lt, matrix_f32* ut, matrix_f32* p){
    uint16_t rows = src->num_rows;
    uint16_t columns = src->num_cols;
    float32_t l;
    int max;

    // Wypełnienie macierzy lt i ut zeramy oraz macierzy lt 1 na przekątnej
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < rows; j++){
            ut->p_data[i*rows+j] = 0;
            lt->p_data[i*rows+j] = 0;
            if(i == j){
                p->p_data[i*rows+j] = 1;
            }
            else{
                p->p_data[i*rows+j] = 0;
            }
        }
    }

    for(int i = 0; i < columns; i++){
        // Wybór elementu głównego
        max = MAX_COL(src, i, i);

        if(max != i){
            SWAP_ROWS(src, i, max);
            SWAP_ROWS(p, i, max);
            SWAP_ROWS(lt, i, max);
        }

        // Zamiana wierszy
        for(int j = i; j < (rows-1); j++){
            // Obliczenie l
            l = src->p_data[(j+1)*columns+i]/src->p_data[i*columns+i];

            for(int z = 0; z < columns; z++){
                src->p_data[(j+1)*columns+z] = src->p_data[(j+1)*columns+z] - l*src->p_data[i*columns+z];
            }

            // Przypisanie wartości l do dolnej macierzy trójkątnej
            lt->p_data[(j+1)*columns+i] = l;
        }
    }

    // Wypełnienie macierzy lt i ut zeramy oraz macierzy lt 1 na przekątnej
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < rows; j++){
            ut->p_data[i*rows+j] = 0;
            if(i == j){
                lt->p_data[i*rows+j] = 1;
            }
        }
    }

   return MATH_SUCCESS;
}

status inverse_matrix_f32(matrix_f32* src, matrix_f32* dst){
    uint16_t rows = src->num_rows;
    uint16_t columns = src->num_cols;

    if(rows != columns){
        // Aby macierz była odwracalna musi być macierzą kwadratową
        return MATH_WRONG_MATRIX_DIMENSIONS;
    }
    else if(rows != dst->num_rows || columns != dst->num_cols){
        // Macierz src i dst muszą mieć  takie same wymiary
        return MATH_WRONG_MATRIX_DIMENSIONS;
    }

    // Wypełnienie macierzy DST jako jednostkowej
    for(uint16_t i = 0; i < rows; i++){
        for(uint16_t j = 0; j < rows; j++){
            if(i == j){
                dst->p_data[i*columns+j] = 1;
            }
            else{
                dst->p_data[i*columns+j] = 0;
            }
        }
    }

    float32_t lt_data[rows*columns];
    float32_t ut_data[rows*columns];
    float32_t buffer_data[rows*columns];
    float32_t p_data[rows*columns];
    float32_t inv_lt_data[rows*columns];
    float32_t inv_ut_data[rows*columns];

    matrix_f32 LT, UT, P, buffer, INV_LT, INV_UT;

    matrix_init_f32(&LT, rows, columns, lt_data);
    matrix_init_f32(&UT, rows, columns, ut_data);
    matrix_init_f32(&P, rows, columns, p_data);
    matrix_init_f32(&buffer, rows, columns, buffer_data);
    matrix_init_f32(&INV_LT, rows, columns, inv_lt_data);
    matrix_init_f32(&INV_UT, rows, columns, inv_ut_data);

    lu_decomposition_f32(src, &LT, &UT, &P);

    INVERSE_TRIANGULAR(&LT, &INV_LT, 0);
    INVERSE_TRIANGULAR(src, &INV_UT, 1);

    matrix_mul_f32(&INV_UT, &INV_LT, &buffer);
    matrix_mul_f32(&buffer, &P, dst);
    return MATH_SUCCESS;
}

status matrix_mul_f32(matrix_f32* a, matrix_f32* b, matrix_f32* dst){
    /// Możliwe wtedy i tylko wtedy gdy liczba kolumn a jest równa liczbie wierszy b
    if(a->num_cols != b->num_rows){
        return MATH_WRONG_MATRIX_DIMENSIONS;
    }

    if(a->num_rows != dst->num_rows || b->num_cols != dst->num_cols){
        return MATH_WRONG_MATRIX_DIMENSIONS;
    }

    uint16_t rows = b->num_cols;
    uint16_t columns = a->num_rows;

    uint16_t common = a->num_cols;

    float32_t sum;
    for(uint16_t k = 0; k < rows; k++){
        for(uint16_t i = 0; i < columns; i++){
            sum = 0;
            for(uint16_t j = 0; j < common; j++){
                sum += a->p_data[k*a->num_cols+j] * b->p_data[j*b->num_cols+i];
            }
            dst->p_data[k*rows+i] = sum;
        }
    }

    return MATH_SUCCESS;
}

status matrix_add(matrix_f32* a, matrix_f32* b, matrix_f32* dst){

}

status matrix_sub(matrix_f32* a, matrix_f32* b, matrix_f32* dst);
