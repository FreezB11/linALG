#include <LinALG/matrix.h>
#include <type_traits>
#include <LinALG/Extern/simde/simde/x86/avx.h>

template<typename T>
T* matrix<T>::flatten() {
    size_t rows = m;
    size_t cols = n;
    T* flat = new T[rows * cols];

    node<T>* curr = matrix_data->head;
    size_t idx = 0;

    while (curr) {
        size_t j = 0;

        if constexpr (std::is_same_v<T, float>) {
            // 8 floats per AVX2 register
            for (; j + 8 <= cols; j += 8) {
                simde__m256 v = simde_mm256_loadu_ps(curr->data + j);
                simde_mm256_storeu_ps(flat + idx, v);
                idx += 8;
            }
        } else if constexpr (std::is_same_v<T, double>) {
            // 4 doubles per AVX2 register
            for (; j + 4 <= cols; j += 4) {
                simde__m256d v = simde_mm256_loadu_pd(curr->data + j);
                simde_mm256_storeu_pd(flat + idx, v);
                idx += 4;
            }
        }

        // Copy remaining elements
        for (; j < cols; ++j)
            flat[idx++] = curr->data[j];

        curr = curr->nxt;
    }

    return flat;
}

// template<typename T>
// T* matrix<T>::flatten() {
//     size_t rows = m;
//     size_t cols = n;
//     T* flat = new T[rows * cols];

//     node<T>* curr = matrix_data->head;
//     size_t row_offset = 0;

//     while (curr) {
//         for (size_t j = 0; j < cols; ++j)
//             flat[row_offset + j] = curr->data[j];
//         row_offset += cols;
//         curr = curr->nxt;
//     }

//     return flat;
// }


template float* matrix<float>::flatten();
template double* matrix<double>::flatten();
template int* matrix<int>::flatten();