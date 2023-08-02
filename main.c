#include <stdio.h>
#include "matrix_math.h"

/*
 *
0.663319 -0.447222 0.600000
0.497489 -0.335417 -0.800000
0.559028 0.829149 0.000000

 Inverse
 0.663319 0.497489 0.559028
-0.447222 -0.335417 0.829149
0.600000 -0.800000 0.000000



 -0.43900374825319494,-0.4089935317577108,0.7999999999999999
0.6816558862628512,-0.7316729137553247,0.0
0.5853383310042597,0.545324709010281,0.6000000000000001

 Inverse
 -0.4390    0.6817    0.5853
   -0.4090   -0.7317    0.5453
    0.8000    0.0000    0.6000


 *
 *
 *
 *
 * */


int main() {
    float mat_a[9] = {
            -0.43900374825319494,-0.4089935317577108,0.7999999999999999,
            0.6816558862628512,-0.7316729137553247,0.0,
            0.5853383310042597,0.545324709010281,0.6000000000000001,

    };

    float mat_dst[9] = {};
    matrix_f32 A, DST;

    matrix_init_f32(&A, 3, 3, mat_a);
    matrix_init_f32(&DST, 3, 3, mat_dst);

    for(int i = 0; i < 3; i ++){
        printf("%f %f %f\n", mat_a[3*i], mat_a[3*i+1], mat_a[3*i+2]);
    }

    inverse_matrix(&A, &DST);

    printf("Inverse\n");
    for(int i = 0; i < 3; i ++){
        printf("%f %f %f\n", mat_dst[3*i], mat_dst[3*i+1], mat_dst[3*i+2]);
    }

    /*// Test mult

    float a[9] = {
            1, 2, 3,
            4, 5, 6,
            1, 2, 3};

    float b[9] = {
            5, 4, 1,
            4, 3, 1,
            99, 21, 1
    };
    float result[9] = {};

    matrix_f32 A_MULT, B_MULT, RESULT;

    matrix_init_f32(&A_MULT, 3, 3, a);
    matrix_init_f32(&B_MULT, 3, 3, b);
    matrix_init_f32(&RESULT, 3, 3, result);

    matrix_mult(&A_MULT, &B_MULT, &RESULT);

    for(int i = 0; i < 3; i ++){
        printf("%f %f %f\n", result[3*i], result[3*i+1], result[3*i+2]);
    }*/

    return 0;
}
