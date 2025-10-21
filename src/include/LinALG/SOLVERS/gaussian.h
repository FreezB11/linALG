/// @file: Gaussian.h
// gaussian method to solve 
// Ax = B
#pragma once
#include <LinALG/matrix.h>
#include <vector>
#include <cmath>

using namespace std;


template<typename T>
vector<T> GaussianElimination(matrix<T>& mat){
    // write error check here
    int n = mat.size();
    vector<T> solution(n);
    for(int k = 0; k<n; ++k){
        int max_row = k;
        for(int i = k+1; i<n; ++i){
            if(abs(mat(i,j)) > abs(mat(max_row,k))){
                max_row = i;
            }
        }
        //swap row
        mat.swap_row(k, max_row);

        if(abs(mat(k,k)) < 1e-9){
            return;
        }
        for(int i = k +1; i < n; ++i){
            double factor  = mat(i,k) / mat(k,k);
            for(int j = k; j < n + 1; ++j){
                mat(i,j) -= factor * mat(k,j);
            }
        }
    }
    for(int i = n-1; i >=0; --i){
        solutions[i] = mat[i][n];
        for(int j = i+1; j<n; ++j){
            solution[i] -= mat(i,j) * solution[j];
        }
        solution[i]  /= mat(i,i);
    }

    return solution;
}