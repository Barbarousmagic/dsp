#include <random>

#include "Tensor.h"
int main() {
    Tensor CSD(20, 20);
    for (size_t i = 0; i < CSD.get_rows(); ++i) {
        for (size_t j = 0; j < CSD.get_cols(); ++j) {
            if (j >= CSD.get_cols() / 2) CSD(i, j) = 1.0;
        }
    }
    std::mt19937 gen(1337);
    std::normal_distribution<double> noise_dist(0.0, 3.0);
    for (size_t i = 0; i < CSD.get_rows(); ++i) {
        for (size_t j = 0; j < CSD.get_cols(); ++j) {
            CSD(i, j) += noise_dist(gen);
        }
    }

    Tensor Filtered(20, 20);
    for (size_t i = 1; i < CSD.get_rows() - 1; ++i) {
        for (size_t j = 1; j < CSD.get_cols() - 1; ++j) {
            Filtered(i, j) = (CSD(i - 1, j - 1) + CSD(i - 1, j) + CSD(i - 1, j + 1)
                                + CSD(i, j - 1) + CSD(i, j) + CSD(i, j + 1)
                                + CSD(i + 1, j + 1) + CSD(i + 1 , j) + CSD(i + 1, j + 1)) / 9.0;
        }
    }
    Filtered.print();
    return 0;
}