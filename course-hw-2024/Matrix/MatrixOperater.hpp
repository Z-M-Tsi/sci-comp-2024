#ifndef MATRIXOPERATOR_HPP
#define MATRIXOPERATOR_HPP
#include "Matrix.h"

namespace mymatrix {
template <typename T>
inline T& Matrix<T>:: operator()(int i, int j)
{
    if (i < 0 || i >= rows || j < 0 || j >= cols)
        throw std::out_of_range("Index out of range");
    return data[i * cols + j];
}

template <typename T>
inline const T& Matrix<T>:: operator()(int i, int j) const
{
    if (i < 0 || i >= rows || j < 0 || j >= cols)
        throw std::out_of_range("Index out of range");
    return data[i * cols + j];
}

template <typename T>
Matrix<T>& Matrix<T>:: operator=(const Matrix<T>& M)
{
    if (this == &M)
        return *this;
    rows = M.rows;
    cols = M.cols;
    data = M.data;
    return *this;
}

template <typename T>
Matrix<T> Matrix<T>::operator+(const Matrix<T>& M) const {
    if (rows != M.rows || cols != M.cols) 
        throw std::invalid_argument("Matrices must have the same dimensions for addition");

    Matrix<T> result(rows, cols);
    for (int i = 0; i < rows * cols; ++i) {
        result.data[i] = data[i] + M.data[i];
    }
    return result; 
}

template <typename T>
Matrix<T> Matrix<T>::operator-(const Matrix<T>& M) const {
    if (rows != M.rows || cols != M.cols) 
        throw std::invalid_argument("Matrices must have the same dimensions for subtraction");

    Matrix<T> result(rows, cols);
    for (int i = 0; i < rows * cols; ++i) {
        result.data[i] = data[i] - M.data[i];
    }
    return result; 
}

template <typename T>
Matrix<T> Matrix<T>::operator*(const Matrix<T>& M) const {
    if (cols != M.rows) 
        throw std::invalid_argument("Invalid dimensions for matrix multiplication");

    Matrix<T> result(rows, M.cols);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < M.cols; ++j) {
            T sum = 0;
            for (int k = 0; k < cols; ++k) {
                sum += data[i*cols+k] * M.data[k*M.cols+j];
            }
            result.data[i*M.cols+j] = sum;
        }
    }
    return result;  
}

template <typename T>
Matrix<T> operator*(const T& scalar, const Matrix<T>& M) {
    Matrix<T> result(M.rows, M.cols);
    for (int i = 0; i < M.rows * M.cols; ++i) {
        result.data[i] = scalar * M.data[i];
    }
    return result;
}

template <typename T>
Matrix<T> operator*(const Matrix<T>& M, const T& scalar) {
    return scalar * M;
}

} // namespace mymatrix


#endif // MATRIXOPERATOR_HPP