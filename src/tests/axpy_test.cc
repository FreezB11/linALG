/// @file axpy_test.cc
#include <LinALG/BLAS/axpy.h>
#include <iostream>

int main(){

    float* A = new float[100];
    float* B = new float[100];
    float* C;

    for(int i = 0; i < 100; i++){
        A[i] = 1.0f;
        B[i] = (i % 10) * 1.3f;
    }

    C = axpy(100, 1.2f, A, B);

    for(int i = 0; i < 100; i++){
        std::cout << C[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}