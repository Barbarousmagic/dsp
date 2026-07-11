#include <iostream>
#include <complex>
#include "QuantumCircuit.h"

int main() {
    QuantumCircuit<std::complex<double>> qc(3, Backend::CudaQGPU);

    std::cout << "[0] Preparing secret state on q[0]...\n";


    std::cout << "[1] Creating Bell pair between q[1] and q[2]...\n";
    qc.h(1);
    qc.cnot(1, 2);

    std::cout << "[2] Alice interacts her qubits...\n";
    qc.cnot(0, 1);
    qc.h(0);

    std::cout << "[3] DEFERRED MEASUREMENT (Quantum Control instead of Classical)...\n";
    qc.cnot(1, 2);


    qc.h(2);
    qc.cnot(0, 2);
    qc.h(2);

    qc.print_circuit();

    std::cout << "\n[INFO] Running teleportation protocol...\n";
    qc.sample(1000);

    return 0;
}