/// @note:
/*
    y <-- alpha*x + y
           ax  p  y
*/

#include <LinALG/Extern/mySIMD.h>
// Detect SIMD support and include the appropriate SIMDe headers
/** 
    @note 
    from here on we will use pointer wised data
    representation only float* and double*
*/

float* axpy(size_t n, float alpha, float* x, float* y){
    // basic code
    /*
        float* data = new float[n];
        for(size_t i = 0; i < n; i++){
            data[i] = alpha*x[i] + y[i];
        }
        return data;
    */
#if defined(__AVX__) || defined(__AVX2__)
   simde__m256 alpha_vec = simde_mm256_set1_ps(alpha);

   size_t i = 0;
    for(; i < n; i += 8){
        simde__m256 x_vec = simde_mm256_loadu_ps(&x[i]);
        simde__m256 y_vec = simde_mm256_loadu_ps(&y[i]);

        simde__m256 mul_vec = simde_mm256_mul_ps(alpha_vec, x_vec);

        simde__m256 add = simde_mm256_add_ps(mul_vec, y_vec);

        simde_mm256_storeu_ps(&y[i], y_vec);
    }
    // handle edge case
    for(; i < n; i++){
        y[i] = alpha * x[i] + y[i];
    }
#else
    for(size_t i = 0; i < n; i++){
        y[i] = alpha * x[i] + y[i];
    }
#endif
    return y;
}

double* axpy(size_t n, double alpha, double* x, double* y){

#if defined(__AVX__) || defined(__AVXX2__)
    simde__m256d alpha_vec = simde_mm256_set1_pd(alpha);
    size_t i = 0;
    for(; i < n; i += 4){
        simde__m256d x_vec = simde_mm256_loadu_pd(&x[i]);
        simde__m256d y_vec = simde_mm256_loadu_pd(&y[i]);

        simde__m256d mul_vec = simde_mm256_mul_pd(alpha_vec, x_vec);

        simde__m256d add = simde_mm256_add_pd(mul_vec, y_vec);

        simde_mm256_storeu_pd(&y[i], y_vec);
    }
    // edge case handle
    for(;i<n; i++){
        y[i] = alpha * x[i] + y[i];
    }
#else
    for(size_t i = 0; i < n; i++){
        y[i] = alpha*x[i] + y[i];
    }
#endif
    return y;
}