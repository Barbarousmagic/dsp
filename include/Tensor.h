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
        if (this->cols != other.rows) {
            throw std::invalid_argument("Dimension mismatch: cols != other.rows");
        }
        Tensor result(this->rows, other.cols);
        for (int i = 0; i < this->rows; ++i) {
            for (int k = 0; k < this->cols; ++k) {
                for (int j = 0; j < other.cols; ++j) {
                    result(i, j) += (*this)(i, k) * other(k, j);
                }
            }
        }
        return result;
    }
    double& operator()(size_t r, size_t c){
        return data[r * cols + c];
    }

    const double& operator()(size_t r, size_t c) const {
        return data[r * cols + c];
    }
};

#endif //LINUXTEST_TENSOR_H
