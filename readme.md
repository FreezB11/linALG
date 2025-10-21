# LinALG

<h2 align="center">
  <a href="https://mlpack.org"><img src="https://upload.wikimedia.org/wikipedia/commons/2/2f/Linear_subspaces_with_shading.svg" style="background-color:rgba(0,0,0,0);" height=230 alt="mlpack: a fast, header-only machine learning library"></a>
  <br>A simple Linear ALGEBRA<br>
</h2>

![GitHub Created At](https://img.shields.io/github/created-at/FreezB11/xmd4)
![GitHub contributors](https://img.shields.io/github/contributors/FreezB11/xmd4)



1. Core Data structures
Matrix
 - Matrix(rows, cols)
 - Identity(n)
 - zeros(rows, cols)
 - ones(rows, cols)
 - random(rows, cols)
 - diagonal(vector<>)
 - fromArray(data, rows, cols)
 - copy()
 - shape() -> (rows, cols)
 - get(rows, cols)
 - set(rows, cols, value)
 - resize(new_rows, new_cols)
 - subMatrix(row_start, row_end, cols_start, cols_end)
 - AppendRow() / AppendCols()
 - Flatten()
Vector
 - vector(n)
 - zeros(n)
 - ones(n)
 - random(n)
 - fromArray(data)
 - dot(other)
 - cross(other)
 - Norm()
 - Normalize()

2. Basix matrix ops
 - Add(a, b)
 - Subtract(a, b)
 - multiply(a, b)
 - multiply(a, x)
 - scalarMultiply(A, k)
 - Divide(a, k)
 - Transpose(a)
 - Hadamard(a, b)
 - determinant(a)
 - Trace(a)
 - Inverse(a)
 - power(a, n)
 - rank(a)
 - Norm(a, type)

3. Matrix constructors and utilities
 - diagonal(a)
 - upperTriangular(a)
 - lowerTriangular(a)
 - isSquare(a)
 - isSymmetric(a)
 - isOrthogonal(a)
 - isDiagonal(a)
 - isInvertable(a)
 - SwapRows(A, i, j)
 - SwapCols(A, i, j)
 - RowSUM(A) / ColSUM(A)
 - max(a) / min(a)
 - fill(a, value)
 - tofile()
 - fromfile()

4. Solving Linear System
for solving Ax=B
 - SolveGaussian(a,b)
 - SolveLU(a,b)
 - SolveCholesky(A,b)
 - SolveQR(a,b)
 - SolveJacobi(a,b) iterative
 - SolveGaussSeidel(A,b)
 - LeastSquares(a, b) (minimize ||Ax-b||^2)

5. Matrix Decompositions
 - LUDecompose(A)
 - QRDecompose(A)
 - CholeskyDecompose(A)
 - SVD(A)
 - Eigen(A)
 - SchurDecompose(A)
 - PolarDecompose(A)

6. additional funcs
 - Mean(vector)
 - Variance(vector)
 - Covariance(matrix)
 - Correlation(matrix)
 - PCA(matrix)
 - Projection(matrix, subspace)
 - RegressionCoeff(x, y)

7. Utilities
i/o
 - load/save matrices in .csv, .txt, .json
benchmarking
 - meausre time for multiply/solve/decompose
random generator
 - uniform, normal, gaussian
SIMD optimization
 - vector based instruction