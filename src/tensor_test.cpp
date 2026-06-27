#include <iostream>
#include <cmath>
#include "Tensor.h"

int main() {
    Tensor qubit(2,1);
    qubit(0, 0) = 1.0;
    qubit(1, 0) = 0.0;
    qubit.print();

    Tensor H(2, 2);
    double inv_sqrt2 = 1.0 / std::sqrt(2.0);
    H(0,0) = inv_sqrt2; H(0, 1) = inv_sqrt2;
    H(1,0) = inv_sqrt2; H(1, 1) = -inv_sqrt2;
    H.print();

    Tensor superposition = H.matmul(qubit);
    superposition.print();
    return 0;
}