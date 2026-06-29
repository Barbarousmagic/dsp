#include <cmath>
#include "Tensor.h"

int main() {
    /*
    Tensor qubit(2,1);
    qubit(0, 0) = 1.0;
    qubit(1, 0) = 0.0;
    qubit.print();

    Tensor H(2, 2);
    double inv_sqrt2 = 1.0 / std::sqrt(2.0);
    H(0,0) = inv_sqrt2; H(0, 1) = inv_sqrt2;
    H(1,0) = inv_sqrt2; H(1, 1) = -inv_sqrt2;
    H.print();

    Tensor superposition = H*(qubit);
    superposition.print();
    Tensor q0(2, 1);
    q0(0, 0) = 1.0;
    q0(1, 0) = 0.0;
    Tensor q1(2, 1);
    q1(0, 0) = 1.0;
    q1(1, 0) = 0.0;
    Tensor q_sys = q0.kronecker(q1);
    q_sys.print();
    Tensor I(2, 2);
    I(0, 0) = 1; I(0, 1) = 0;
    I(1, 0) = 0; I(1, 1) = 1;
    Tensor H_sys = H.kronecker(I);
    H_sys.print();
    Tensor CNOT(4, 4);
    CNOT(0, 0) = 1.0;
    CNOT(1, 1) = 1.0;
    CNOT(2, 3) = 1.0;
    CNOT(3, 2) = 1.0;
    Tensor step1 = H_sys*(q_sys);
    Tensor entangled = CNOT*(step1);
    entangled.print();
    */
    std::cout << "--- Testing Matrix Inversion ---\n";
    Tensor A(2, 2);
    A(0, 0) = 2.0; A(0, 1) = 1.0;
    A(1, 0) = 4.0; A(1, 1) = 3.0;

    std::cout << "Original Matrix A:\n";
    A.print();

    Tensor A_inv = A.inverse();
    std::cout << "\nInverse Matrix A^-1:\n";
    A_inv.print();

    Tensor Identity = A * A_inv;
    std::cout << "\nVerification (A * A^-1 = I):\n";
    Identity.print();
    return 0;
}