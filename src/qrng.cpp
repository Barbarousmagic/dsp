
#include "Tensor.h"

#include <iostream>
#include <cmath>
#include <random>

int main() {
    Tensor q0(2, 1);
    q0(0, 0) = 1.0;
    std::cout << "initial state |0>:\n";
    q0.print();

    Tensor H(2, 2);
    double inv_sqrt2 = 1.0 / std::sqrt(2);
    H(0, 0) = inv_sqrt2; H(0, 1) = inv_sqrt2;
    H(1, 0) = inv_sqrt2; H(1, 1) = -inv_sqrt2;
    std::cout << "Hadamard Gate (H):" << std::endl;
    H.print();

    Tensor superposition = H.matmul(q0);
    std::cout << "Superposition state |+>: \n";
    superposition.print();

    double prob0 = std::pow(superposition(0, 0), 2);
    double prob1 = std::pow(superposition(1, 0), 2);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dist(0.0, 1.0);
    double roll = dist(gen);

    std::cout << "\n--- Measurements ---" << std::endl;
    std::cout << "Probabilities: |0>: " << prob0 << ", |1>: " << prob1 << std::endl;
    if (roll < prob0) {
        std::cout << "Measurement result: 0" << std::endl;
    } else {
        std::cout << "Measurement result: 1" << std::endl;
    }
    return 0;
}