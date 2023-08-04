#include "../include/utilities.h"

uint16_t MAX_COL(matrix_f32* matrix, uint16_t start_row, uint16_t column){
    int max_index = start_row;

    float32_t max_value = fabsf(matrix->p_data[start_row*matrix->num_cols+column]);

    for(int i = start_row; i < matrix->num_rows; i++){
        if(fabsf(matrix->p_data[i*matrix->num_cols+column]) > max_value){
            max_index = i;
        }
    }
    return max_index;
}

/// Zamiana A z B, A idzie na miejsce B
void SWAP_ROWS(matrix_f32* matrix, uint16_t row_a, uint16_t row_b){
    float32_t buffer;

    for(int i = 0; i < matrix->num_cols; i++){
        buffer = matrix->p_data[row_b*matrix->num_cols+i];
        matrix->p_data[row_b*matrix->num_cols+i] = matrix->p_data[row_a*matrix->num_cols+i];
        matrix->p_data[row_a*matrix->num_cols+i] = buffer;
    }
}


void INVERSE_TRIANGULAR(matrix_f32* src, matrix_f32* inv, uint8_t upper){
    /// Dodać jeszcze obejście algorytmu odwracania, jeżeli mamy na diagonali same 1
    /// Wtedy odwrotna macierz to po prostu macierz ze zmienionymi znakami

    float32_t coeff;

    uint16_t rows = src->num_rows;
    uint16_t columns = src->num_cols;

    for(int i = 0; i < rows; i++){
        for(int j = 0; j < columns; j++){
            if(i == j){
                inv->p_data[i*rows+j] = 1;
            }
            else{
                inv->p_data[i*rows+j] = 0;
            }
        }
    }

    if(upper == 0){
        for(int i = 0; i < columns; i++){
            for(int j = i; j < rows; j++){
                if(i == j){
                    coeff = 1/src->p_data[i*columns+j];
                }
                else{
                    coeff = -src->p_data[j*columns+i];
                }

                for(int z = 0; z < columns; z++){
                    if(i == j){
                        src->p_data[j*columns+z] = coeff*src->p_data[i*columns+z];
                        inv->p_data[j*columns+z] = coeff*inv->p_data[i*columns+z];
                    }
                    else{
                        src->p_data[j*columns+z] = src->p_data[j*columns+z] + coeff*src->p_data[i*columns+z];
                        inv->p_data[j*columns+z] = inv->p_data[j*columns+z] + coeff*inv->p_data[i*columns+z];
                    }
                }
            }

        }
    }
    else{
        for(int i = rows-1; i >= 0; i--){
            for(int j = i; j >= 0; j--){
                if(i == j){
                    coeff = 1/src->p_data[i*columns+j];
                }
                else{
                    coeff = -src->p_data[j*columns+i];
                }

                for(int z = 0; z < columns; z++){
                    if(i == j){
                        src->p_data[j*columns+z] = coeff*src->p_data[i*columns+z];
                        inv->p_data[j*columns+z] = coeff*inv->p_data[i*columns+z];
                    }
                    else{
                        src->p_data[j*columns+z] = src->p_data[j*columns+z] + coeff*src->p_data[i*columns+z];
                        inv->p_data[j*columns+z] = inv->p_data[j*columns+z] + coeff*inv->p_data[i*columns+z];
                    }
                }
            }

        }
    }
}