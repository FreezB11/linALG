/// @file: matrix.h
#pragma once
#include <cstddef>
#include <vector>
#include <iostream>
#include <cstring>
#include <cstdlib> // for rand()
#include <ctime>  // for time()
#include <LinALG/DATASTRUCTURES/linkedlist.h>

#define _resize false
#ifdef RESIZE_TRUE
    #define _resize true
#endif

typedef size_t idx;
using namespace std;

template< typename T>
class matrix{
private:
    // old of storing the matrix
    // T* data;
    // new method
    linkedlist<T>* matrix_data;
    size_t m, n;
    bool useCPU = false;
public:
    // default constructor
    matrix() :m(0), n(0),matrix_data(nullptr){};
    // parametric constructor
    matrix(int m, int n) : m(m), n(n) {
        // data = new T[m * n];
        // memset(data, 0, sizeof(T) * m * n);
        matrix_data = new linkedlist<T>(m,n);
    };
    // to make square matrix
    matrix(int n) :m(n), n(n){
        // data = new T[n * n];
        // memset(data, 0, sizeof(T) * n * n);
        matrix_data = new linkedlist<T>(n, n);
    };
    // copy constructor
    matrix(matrix<T>& other){
        m = other.m;
        n = other.n;
        // data = new T[m * n];
        // memcpy(data, other.data, sizeof(T) * m * n);
        matrix_data = new linkedlist<T>(m,n);
        node<T>* src = other.matrix_data->head;
        node<T>* dst = matrix_data->head;
        while(src && dst){
            memcpy(dst->data, src->data, sizeof(T)*n);
            src = src->nxt;
            dst = dst->nxt;
        }
    };
    int rows(){
        return this->m;
    }
    int cols(){
        return this->n;
    }
    // Assignment operator
    // matrix<T>& operator=(const matrix<T>& other){
    //     if (this == &other) return *this; // self-assignment check
    //     delete[] data;
    //     m = other.m;
    //     n = other.n;
    //     data = new T[m * n];
    //     memcpy(data, other.data, sizeof(T) * m * n);
    //     return *this;
    // };
    matrix<T>& operator=(const matrix<T>& other) { 
        if (this == &other) return *this; 
        delete matrix_data; 
        m = other.m; 
        n = other.n; 
        matrix_data = new linkedlist<T>(m, n); 
        node<T>* src = other.matrix_data->head; 
        node<T>* dst = matrix_data->head; 
        while (src && dst) { 
            memcpy(dst->data, src->data, sizeof(T) * n); 
            src = src->nxt; 
            dst = dst->nxt; 
        } 
        return *this; 
    }
    void fill(T value) {
        // for (size_t i = 0; i < m * n; ++i)
        //     data[i] = value;
        node<T>* curr = matrix_data->head;
        while(curr){
            for(size_t j = 0; j< n; j++)
                curr->data[j] = value;
            curr = curr->nxt;
        }
    }

    void print() const {
        // for (size_t i = 0; i < m; ++i) {
        //     for (size_t j = 0; j < n; ++j)
        //         cout << data[i * n + j] << " ";
        //     cout << "\n";
        // }
        node<T>* curr = matrix_data->head;
        while(curr){
            for(size_t j = 0; j < n; j++)
                cout << curr->data[j] << " ";
            cout << "\n";
            curr = curr->nxt;
        }
    }
    // will return the shape (m,n)
    void shape();
    // to get the value at (x,y)
    T get(idx x, idx y);
    
    //element access (x,y)
    T& operator()(idx x, idx y){
        // return data[x*m + y];
        node<T>* curr = matrix_data->head;
        for(size_t i = 0; i < x && curr; ++i)
            curr = curr->nxt;
        if(!curr) throw out_of_range("Row index out of range");
        return curr->data[y];
    };

    // Function to swap two rows
    void swap_row(idx row1, idx row2) {
        if (row1 >= m || row2 >= m) {
            throw std::out_of_range("Row index out of range");
        }
        if (row1 == row2) return; // Nothing to do
        
        // node<T>* r1 = matrix_data->head;
        // node<T>* r2 = matrix_data->head;
        // for(size_t i = 0; i < row1; i++) r1 = r1->nxt;
        // for(size_t i = 0; i < row2; i++) r2 = r2->nxt;

        // for (size_t j = 0; j < n; j++)
        //     swap(r1->data[j], r2->data[j]);
        
        // for (size_t col = 0; col < n; ++col) {
        //     std::swap((*this)(row1, col), (*this)(row2, col));
        // }

        node<T>* prev1 = nullptr;
        node<T>* prev2 = nullptr;
        node<T>* curr1 = matrix_data->head;
        node<T>* curr2 = matrix_data->head;

        for(size_t i = 0; i < row1; i++){
            prev1 = curr1;
            curr1 = curr1->nxt;
        }
        for(size_t i = 0; i < row2; i++){
            prev2 = curr2;;
            curr2 = curr2->nxt;
        }
         // Now swap their links
        if (prev1) prev1->nxt = curr2;
        if (prev2) prev2->nxt = curr1;

        // Swap the 'nxt' pointers of the two nodes
        node<T>* temp = curr1->nxt;
        curr1->nxt = curr2->nxt;
        curr2->nxt = temp;

        // if we swapped the head, fix it
        if(row1 == 0) matrix_data->head = curr2;
        else if(row2 == 0) matrix_data->head = curr1;
    }
    // to set given value at (x, y)
    // this will be a bool to get a error if x,y is out of bounds
    bool set(idx x, idx y, T value){
        node<T>* curr = matrix_data->head;
        for(size_t i = 0; i < x && curr; i++)
            curr = curr->nxt;
        if(!curr) return false;
        curr->data[y] = value;
        return true;
    };
    // resize the matrix from MxN to M_new x N_new
    // we shall return nothing as this operation 
    // will either make a big or small matrix with no error possible
    void resize(size_t M, size_t N);
    // we shall return a sub matrix
    // the return will a matrix<T>
    matrix<T>& submatrix(idx start_x, idx start_y, size_t m, size_t n);
    // when a square matrix 
    size_t size(){
        return n;
    }
    // to initialize it with values
    matrix<T>& zeros(){
        node<T>* curr = matrix_data->head;
        while(curr){
            for(size_t j = 0; j < n; j++)
                curr->data[j] = static_cast<T>(0);
            curr = curr->nxt;
        }
        return *this;
    };

    matrix<T>& ones(){
        node<T>* curr = matrix_data->head;
        while(curr){
            for(size_t j = 0; j < n; j++)
                curr->data[j] = static_cast<T>(1);
            curr = curr->nxt;
        }
        return *this;
    };

    matrix<T>& random(){
        // we will set the values between 0~1
        srand(static_cast<unsigned>(time(nullptr))); // seed once per run

        node<T>* curr = matrix_data->head;
        while(curr){
            for(size_t j = 0; j < n; j++)
                curr->data[j] = static_cast<T>(rand()) / static_cast<T>(RAND_MAX);
            curr = curr->nxt;
        }
        return *this;
    };

    matrix<T>& identity(){
        if( m!=n) 
            throw runtime_error("matrix must be a square");

        node<T>* curr = matrix_data->head;
        size_t i = 0;
        
        while(curr){
            for(size_t j = 0; j < n; j++){
                curr->data[j] = (i == j) ? static_cast<T>(1) : static_cast<T>(0);
            }
            curr = curr->nxt;
            ++i;
        }
        return *this;
    };

    matrix<T>& fromARRAY(vector<T> data){
        if(data.size() != m * n)
            throw invalid_argument("data size must match matrix dimensions");

        node<T>* curr = matrix_data->head;
        size_t index = 0;

        while(curr){
            for(size_t j = 0; j < n; j++){
                curr->data[j] = data[index++];
            }
            curr = curr->nxt;
        }

        return *this;
    };
    matrix<T>& fromARRAY(T* data){
        // we have to think for some 
        // sort of sanity check
        node<T>* curr = matrix_data->head;
        size_t index = 0;
        while(curr){
            for(size_t j = 0; j < n; j++){
                curr->data[j] = data[index++];
            }
            curr = curr->nxt;
        }
        return *this;
    };

    matrix<T>& diagonal(/* vector input */ vector<T> data){
        if( m != n) 
            throw runtime_error("matrix must be a square to set diagonal");
        if (data.size() != n)
            throw invalid_argument("diagonal size must be equal to matrix dims");

        node<T>* curr = matrix_data->head;
        size_t i = 0;

        while(curr){
            for(size_t j = 0; j < n; j++){
                curr->data[j] = (i==j) ? data[i] : 0;
            }
            curr = curr->nxt;
            ++i;
        }

        return *this;
    };

    matrix<T>& diagonal(T* data){
        if( m != n) 
            throw runtime_error("matrix must be a square to set diagonal");
        
        node<T>* curr = matrix_data->head;
        size_t i = 0;

        while(curr){
            for(size_t j = 0; j < n; j++){
                curr->data[j] = ( i == j) ? data[i] : 0;
            }
            curr = curr->nxt;
            i++;
        }
        return *this;
    };
    // uppperTriangular();
    // lowerTriangular();

    // opperators
    // we will do both operator overloading and 
    // and normal function based operation calls
    matrix<T>& add(matrix<T>& other);
    matrix<T>& operator+(matrix<T>& other);
    // subtract();
    matrix<T>& multiply(matrix<T>& other);
    // sclarMultiply();
    // Divide();
    // this transpose is for different 
    // dimension matrix that is non-square
    matrix<T>& Transpose(){
        matrix<T> result(n,m); // here the dimension is swapped
        node<T>* row = matrix_data->head;

        size_t i = 0;
        while(row){
            for(size_t j = 0; j < n; j++){
                // set the result[j][i] = row->data[j]
                node<T>* transRow = result.matrix_data->head;
                for(size_t k = 0; k < j && transRow; k++){
                    transRow = transRow->nxt;
                }
                if (transRow)
                    transRow->data[i] = row->data[j];
            }
            row = row->nxt;
            ++i;
        }
    };
    // we will do a in-place for square matrix
    // should be faster and less memory
    void transposeInPlace(){
        if(m != n) throw runtime_error("in- place transpose only valid for square matrix");

        node<T>* row_i = matrix_data->head;
        for(size_t i = 0; i < m; i++){
            node<T>* row_j = row_i->nxt;
            for(size_t j = i + 1; j < n; j++){
                T temp = row_i->data[j];
                row_j->data[i] = temp;
                row_j = row_j->nxt;
            }
            row_i = row_i->nxt;
        }
    }
    // Hadamard();
    // determinant();
    // the sum of diagonal is the trace
    T Trace();
    matrix<T>& Inverse();
    // power();
    // int rank();
    // Norm();

    bool isSquare();
    bool isSymmetric();
    bool isOrthogonal();
    bool isDiagonal();
    bool isInvertable();

    T* flatten(); // <-- implementation in different file flatten.cc
    void unflatten(T* flat);

    bool toFile();
    bool fromFile();

    ~matrix(){
        if (matrix_data) {
        delete matrix_data;
        matrix_data = nullptr;
    }
    }
};

typedef matrix<float>  matrixF;
typedef matrix<int>    matrixInt;
typedef matrix<double> matrixD;