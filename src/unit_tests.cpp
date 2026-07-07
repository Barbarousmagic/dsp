#include <iostream>
#include <complex>
#include <cmath> // Для константы M_PI
#include "QuantumCircuit.h"

int main() {
    QuantumCircuit<std::complex<double>> qc(2, Backend::CudaQGPU);

    std::cout << "[1] Layouting parametric circuit...\n";
    qc.h(0);
    qc.cnot(0, 1);
    qc.rx(M_PI, 1);
    qc.print_circuit();
    std::cout << "[2] Executing on NVIDIA...\n";
    qc.sample(1000);

    return 0;
}