//
// Created by novod on 26.06.2026.
//

#ifndef LINUXTEST_TENSOR_H
#define LINUXTEST_TENSOR_H
#include <stdexcept>
#include <vector>
#include <iostream>
#include <cmath>

template <typename T>
class Tensor {
private:
    size_t rows;
    size_t cols;
    std::vector<T> data;
public:
    Tensor (size_t r, size_t c) : rows(r), cols(c) {
        data.resize(rows * cols, T{});
    }
    Tensor<T> matmul(const Tensor<T>& other) const {
        if (cols != other.rows) {
            throw std::invalid_argument("Dimension mismatch: cols != other.rows");
        }
        Tensor result(rows, other.cols);
        for (int i = 0; i < rows; ++i) {
            for (int k = 0; k < cols; ++k) {
                for (int j = 0; j < other.cols; ++j) {
                    result(i, j) += (*this)(i, k) * other(k, j);
                }
            }
        }
        return result;
    }

    Tensor<T> matmul_slow(const Tensor<T>& other) const {
        if (cols != other.rows) {
            throw std::invalid_argument("Dimension mismatch: cols != other.rows");
        }
        Tensor result(rows, other.cols);
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                for (int k = 0; k < other.cols; ++k) {
                    result(i, j) += (*this)(i, k) * other(k, j);
                }
            }
        }
        return result;
    }

    Tensor<T> add(const Tensor<T>& other) const {
        if (cols != other.cols || rows != other.rows) {
            throw std::invalid_argument("Dimension mismatch");
        }
        Tensor<T> result(rows, cols);
        for (size_t i = 0; i < data.size(); ++i) {
            result.data[i] =  data[i] + other.data[i];
        }
        return result;
    }
    Tensor<T> transpose() const {
        Tensor<T> result(cols, rows);
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) result(j, i) = (*this)(i, j);
        }
        return result;
    }

    Tensor<T> kronecker(const Tensor& other) const {
        Tensor<T> result(rows * other.rows, cols * other.cols);
        for (size_t rA = 0; rA < rows; ++rA) {
            for (size_t cA = 0; cA < cols; ++cA) {
                for (size_t rB = 0; rB < other.rows; ++rB) {
                    for (size_t cB = 0; cB < other.cols; ++cB) {
                        result(rA * other.rows + rB, cA * other.cols + cB) = (*this)(rA, cA) * other(rB, cB);
                    }
                }
            }
        }
        return result;
    }

    Tensor<T> inverse() const {
        if (rows != cols) {
            throw std::invalid_argument("Matrix is not square");
        }
        Tensor<T> A = *this;
        Tensor<T> result (rows, cols);
        for (size_t i = 0; i < rows; ++i) result(i, i) = 1.0;
        for (size_t i = 0; i < rows; ++i) {
            T pivot = A(i, i);
            if (std::abs(pivot) == 0.0) {
                throw std::runtime_error("Zero pivot encountered, matrix is singular");
            }
            for (size_t j = 0; j < cols; j++) {
                A(i, j) /= pivot;
                result(i, j) /= pivot;
            }
            for (size_t k = 0; k < rows; k++) {
                if (k == i) continue;
                T factor = A(k, i);
                for (size_t j = 0; j < cols; j++) {
                    A(k, j) -= factor * A(i, j);
                    result(k, j) -= factor * result(i, j);
                }
            }
        }
        return result;
    }

    Tensor<T> change_basis(const Tensor<T>& P) const {
        if (cols == 1) return P.inverse() * (*this);
        else if (rows == cols) return P.inverse() * (*this) * P;
        else throw std::invalid_argument("Cannot change basis for non-square and non-vector tensors");
    }
    void print() const {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) std::cout << (*this)(i, j) << "\t";
            std::cout << "\n";
        }
    }
    size_t get_rows() const { return rows; }
    size_t get_cols() const { return cols; }

    T& operator()(const size_t r, const size_t c) {
        return data[r * cols + c];
    }

    const T& operator()(const size_t r, const size_t c) const {
        return data[r * cols + c];
    }

    Tensor<T> operator+(const Tensor<T>& other) const {
        return this->add(other);
    }

    Tensor<T> operator*(const Tensor<T>& other) const {
        return this->matmul(other);
    }

    static Tensor Identity() {
        Tensor I(2, 2);
        I(0, 0) = 1.0; I(0, 1) = 0.0;
        I(1, 0) = 0.0; I(1, 1) = 1.0;
        return I;
    }
    static Tensor Hadamard() {
        Tensor H(2, 2);
        double inv_sqrt2 = 1.0 / std::sqrt(2.0);
        H(0, 0) = inv_sqrt2;  H(0, 1) = inv_sqrt2;
        H(1, 0) = inv_sqrt2;  H(1, 1) = -inv_sqrt2;
        return H;
    }

    static Tensor<T> X() {
        Tensor<T> PauliX(2, 2);
        PauliX(0, 0) = 0.0; PauliX(0, 1) = 1.0;
        PauliX(1, 0) = 1.0; PauliX(1, 1) = 0.0;
        return PauliX;
    }

    static Tensor<T> Y() {
        Tensor<T> PauliY(2, 2);
        PauliY(0, 0) = T{0.0};
        PauliY(0, 1) = T{0.0, -1.0}; // -i
        PauliY(1, 0) = T{0.0, 1.0}; // i
        PauliY(1, 1) = T{0.0};
        return PauliY;
    }

    static Tensor Z() {
        Tensor PauliZ(2, 2);
        PauliZ(0, 0) = 1.0; PauliZ(0, 1) = 0.0;
        PauliZ(1, 0) = 0.0; PauliZ(1, 1) = -1.0;
        return PauliZ;
    }
    static Tensor CNOT() {
        Tensor matrix(4, 4);
        matrix(0, 0) = 1.0;
        matrix(1, 1) = 1.0;
        matrix(2, 3) = 1.0; // Changes |10> and |11>
        matrix(3, 2) = 1.0;
        return matrix;
    }
    static Tensor P0() {
        Tensor matrix(2, 2);
        matrix(0, 0) = 1; matrix(0, 1) = 0;
        matrix(1, 0) = 0; matrix(1, 1) = 0;
        return matrix;
    }
    static Tensor P1() {
        Tensor matrix(2, 2);
        matrix(0, 0) = 0; matrix(0, 1) = 0;
        matrix(1, 0) = 0; matrix(1, 1) = 1;
        return matrix;
    }
};

#endif //LINUXTEST_TENSOR_H
