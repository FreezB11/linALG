#include <LinALG/matrix.h>
#include <cblas.h>
#include <iostream>

extern "C" void cublas_multiply_f(const float*, const float*, float*, int, int, int);

template<typename T>
void matrix<T>::unflatten(T* flat) {
    node<T>* curr = matrix_data->head;
    size_t idx = 0;
    while (curr) {
        for (size_t j = 0; j < n; ++j)
            curr->data[j] = flat[idx++];
        curr = curr->nxt;
    }
}


template<>
matrix<float>& matrix<float>::multiply(matrix<float>& other) {
    if(this->useCPU){
    if (n != other.m) throw runtime_error("Matrix size mismatch");
    float* A = this->flatten();
    float* B = other.flatten();

    // matrix<float>* result = new matrix<float>(m, other.n);
    matrix<float> result(m, other.n);
    // float* C = result.flatten();
    float* C = new float[m * other.n];

    cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans,
                m, other.n, n,
                1.0f, A, n,
                B, other.n,
                0.0f, C, other.n);

    result.unflatten(C);

    *this = result;
    delete[] A;
    delete[] B;
    delete[] C;

    return *this;

    }else{
        //gpu code
        if (n != other.m) throw runtime_error("Matrix size mismatch");

        float* A = this->flatten();
        float* B = other.flatten();
        
        matrix<float> result(m, other.n);
        // float* C = result.flatten();
        float* C = new float[m * other.n];

        cublas_multiply_f(A, B, C, m, other.n, n);

        result.unflatten(C);
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
    // float* C = result.flatten();
    double* C = new double[m * other.n];

    cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans,
                m, other.n, n,
                1.0, A, n,
                B, other.n,
                0.0, C, other.n);

    result.unflatten(C);
    *this = result;

    delete[] A;
    delete[] B;
    delete[] C;
    
    return *this;
}
