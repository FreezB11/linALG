#include <LinALG/matrix.h>
#include <cblas.h>
#include <iostream>

extern "C" void cublas_multiply_f(const float*, const float*, float*, int, int, int);

template<>
matrix<float>& matrix<float>::multiply(matrix<float>& other) {
    if(this->useCPU){
    if (n != other.m) throw runtime_error("Matrix size mismatch");
    float* A = this->flatten();
    float* B = this->flatten();

    // matrix<float>* result = new matrix<float>(m, other.n);
    matrix<float> result(m, other.n);
    float* C = result.flatten();

    cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans,
                m, other.n, n,
                1.0f, A, n,
                B, other.n,
                0.0f, C, other.n);

    *this = result;
    delete[] A;
    delete[] B;
    delete[] C;

    return *this;

    }else{
        //gpu code
        if (n != other.m) throw runtime_error("Matrix size mismatch");

        float* A = this->flatten();
        float* B = this->flatten();
        
        matrix<float> result(m, other.n);
        float* C = result.flatten();

        cublas_multiply_f(A, B, C, m, other.n, n);

        *this = result;
        
        delete[] A;
        delete[] B;
        delete[] C;

        return *this;
    }
}

template<>
matrix<double>& matrix<double>::multiply(matrix<double>& other) {
    if (n != other.m) throw runtime_error("Matrix size mismatch");

    double* A = this->flatten();
    double* B = other.flatten();

    matrix<double> result(m, other.n);
    double* C = result.flatten();

    cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans,
                m, other.n, n,
                1.0, A, n,
                B, other.n,
                0.0, C, other.n);

    *this = result;

    delete[] A;
    delete[] B;
    delete[] C;
    
    return *this;
}
