#include <gtest/gtest.h>
#include "Tensor.h"
#include <complex>

#include "QuantumCircuit.h"

TEST(TensorMathTest, RealAddition) {
    Tensor<double> A(2, 2);
    A(0, 0) = 1.0; A(0, 1) = 2.0;
    A(1, 0) = 3.0; A(1, 1) = 4.0;

    Tensor<double> B(2, 2);
    B(0, 0) = 0.5; B(0, 1) = 0.5;
    B(1, 0) = 0.5; B(1, 1) = 0.5;

    Tensor<double> C = A + B;

    EXPECT_EQ(C(0, 0), 1.5);
    EXPECT_EQ(C(1, 1), 4.5);
}

TEST(QuantumSimulationTest, ComplexPauliY) {
    Tensor<std::complex<double>> q0(2, 1);
    q0(0, 0) = std::complex<double>(1.0, 0.0);
    q0(1, 0) = std::complex<double>(0.0, 0.0);

    Tensor<std::complex<double>> Y = Tensor<std::complex<double>>::Y();
    Tensor<std::complex<double>> res = Y * q0;

    EXPECT_EQ(res(0, 0), std::complex<double>(0.0, 0.0));
    EXPECT_EQ(res(1, 0), std::complex<double>(0.0, 1.0));
}

TEST(QuantumCircuitTest, HadamardExecution) {
    QuantumCircuit<double> qc(2);
    std::cout << "\n[INFO] State BEFORE Hadamard Gate:\n";
    qc.print_state();
    qc.h(0);
    std::cout << "\n[INFO] State AFTER Hadamard Gate:\n";
    qc.print_state();
    SUCCEED();
}

TEST(QuantumCircuitTest, BellStatePreparation) {
    QuantumCircuit<double> qc(2);
    qc.h(0);
    qc.cnot(0, 1);
    std::cout << "\n[INFO] Resulting Bell State amplitudes:\n";
    qc.print_state();

    SUCCEED();
}