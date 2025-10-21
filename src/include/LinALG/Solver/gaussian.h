/// @file: Gaussian.h
// gaussian method to solve 
// Ax = B
#pragma once
#include <LinALG/matrix.h>
#include <vector>
#include <cmath>
#include <stdexcept>

using namespace std;

template<typename T>
vector<T> GaussianElimination(matrix<T>& mat) {
    int rows = mat.rows();
    int cols = mat.cols();

    if (cols != rows + 1)
        throw runtime_error("Augmented matrix must have n+1 columns for n equations.");

    vector<T> solution(rows);

    for (int k = 0; k < rows; ++k) {
        int max_row = k;
        for (int i = k + 1; i < rows; ++i) {
            if (abs(mat(i, k)) > abs(mat(max_row, k))) {
                max_row = i;
            }
        }

        if (max_row != k)
            mat.swap_row(k, max_row);

        if (abs(mat(k, k)) < 1e-9)
            throw runtime_error("Matrix is singular or nearly singular");

        for (int i = k + 1; i < rows; ++i) {
            double factor = mat(i, k) / mat(k, k);
            for (int j = k; j < cols; ++j) {
                mat(i, j) -= factor * mat(k, j);
            }
        }
    }

    // Back substitution
    for (int i = rows - 1; i >= 0; --i) {
        solution[i] = mat(i, cols - 1);
        for (int j = i + 1; j < rows; ++j) {
            solution[i] -= mat(i, j) * solution[j];
        }
        solution[i] /= mat(i, i);
    }

    return solution;
}
