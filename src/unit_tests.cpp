#include <iostream>
#include <complex>
#include "QuantumCircuit.h"

int main() {
    QuantumCircuit<std::complex<double>> qc(2, Backend::CudaQGPU);

    std::cout << "[1] Layouting circuit...\n";
    qc.h(0);
    qc.cnot(0, 1);

    std::cout << "[2] Executing simulation...\n";
    qc.sample(1000);

    return 0;
}