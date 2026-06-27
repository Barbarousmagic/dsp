//
// Created by novod on 26.06.2026.
//

#ifndef LINUXTEST_TENSOR_H
#define LINUXTEST_TENSOR_H
#include <stdexcept>
#include <vector>

class Tensor {
private:
    size_t rows;
    size_t cols;
    std::vector<double> data;
public:
    Tensor (size_t r, size_t c) : rows(r), cols(c) {
        data.resize(rows * cols, 0.0);
    }
    Tensor matmul(const Tensor& other) const {
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

    Tensor add(const Tensor& other) const {
        if (cols != other.cols || rows != other.rows) {
            throw std::invalid_argument("Dimension mismatch");
        }
        Tensor result(rows, cols);
        for (size_t i = 0; i < data.size(); ++i) {
            result.data[i] =  data[i] + other.data[i];
        }
        return result;
    }
    Tensor transpose() const {
        Tensor result(cols, rows);
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) result(j, i) = (*this)(i, j);
        }
        return result;
    }

    Tensor kronecker(const Tensor& other) const {
        Tensor result(rows * other.rows, cols * other.cols);
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                for (size_t k = 0; k < other.rows; ++k) {
                    for (size_t l = 0; l < other.cols; ++l) {
                        result(i * other.rows + k, j * other.cols + l) = (*this)(i, j) * other(k, l);
                    }
                }
            }
        }
        return result;
    }

    void print() const {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) std::cout << (*this)(i, j) << "\t";
            std::cout << "\n";
        }
    }

    double& operator()(size_t r, size_t c){
        return data[r * cols + c];
    }

    const double& operator()(size_t r, size_t c) const {
        return data[r * cols + c];
    }
};

#endif //LINUXTEST_TENSOR_H
