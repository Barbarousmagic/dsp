//
// Created by novod on 02.07.2026.
//

#ifndef LINUXTEST_QUANTUMCIRCUIT_H
#define LINUXTEST_QUANTUMCIRCUIT_H

#include <vector>
#include <cudaq.h>
#include <iostream>
#include "Tensor.h"

enum class Backend {
    CustomCPU,
    CudaQGPU
};
enum class GateType { H, CNOT, X, Y, Z, RX, RY, RZ };
struct Operation {
    GateType type;
    size_t target;
    size_t control;
    double angle;
    size_t classical_control;
};
template <typename T>
class QuantumCircuit {
private:
    size_t num_qubits;
    std::vector<Operation> operations;
    Tensor<T> state;
    Backend backend;
public:
    QuantumCircuit(size_t qubits, Backend b = Backend::CustomCPU)
        : num_qubits(qubits), backend(b), state(1 << qubits, 1) {
        if (backend == Backend::CustomCPU) state(0, 0) = T{1.0}; // start state |00...0>
    }
    void print_state() const { state.print(); }
    // --- Phase 1: circuit layout ---
    // basic gates:
    void h(size_t target) { operations.push_back({GateType::H, target, static_cast<size_t>(-1), 0.0, static_cast<size_t>(-1)}); }
    void cnot(size_t control, size_t target) { operations.push_back({GateType::CNOT, target, control, 0.0, static_cast<size_t>(-1)}); }

    // Pauli matrix
    void x(size_t target) { operations.push_back({GateType::X, target, static_cast<size_t>(-1), 0.0, static_cast<size_t>(-1)}); }
    void y(size_t target) { operations.push_back({GateType::Y, target, static_cast<size_t>(-1), 0.0, static_cast<size_t>(-1)}); }
    void z(size_t target) { operations.push_back({GateType::Z, target, static_cast<size_t>(-1), 0.0, static_cast<size_t>(-1)}); }

    // parametric rotates
    void rx(double angle, size_t target) { operations.push_back({GateType::RX, target,
        static_cast<size_t>(-1), angle, static_cast<size_t>(-1)}); }
    void ry(double angle, size_t target) { operations.push_back({GateType::RY, target,
        static_cast<size_t>(-1), angle, static_cast<size_t>(-1)}); }
    void rz(double angle, size_t target) { operations.push_back({GateType::RZ, target,
        static_cast<size_t>(-1), angle, static_cast<size_t>(-1)}); }

    // --- Phase 2: Running
    void sample(int shots = 1000) {
        if (backend == Backend::CustomCPU) {
            std::cout << "[INFO] Running on custom CPU Tensor Engine...\n";
            execute_cpu();
            state.print();
        } else if (backend == Backend::CudaQGPU) {
            std::cout << "[INFO] Running on CUDA-Q GPU...\n";
            execute_cudaq(shots);
        }
    }
    // --- Circuit visualisation ---
    void print_circuit() const {
        std::cout << "\n=== Quantum Circuit ===\n";
        for (size_t i = 0; i < num_qubits; ++i) {
            std::cout << "q[" << i << "]: --";
            for (const auto& op : operations) {
                if (op.target == i) {
                    switch (op.type) {
                        case GateType::H:    std::cout << "[ H ]--"; break;
                        case GateType::X:    std::cout << "[ X ]--"; break;
                        case GateType::Y:    std::cout << "[ Y ]--"; break;
                        case GateType::Z:    std::cout << "[ Z ]--"; break;
                        case GateType::RX:   std::cout << "[Rx ]--"; break;
                        case GateType::RY:   std::cout << "[Ry ]--"; break;
                        case GateType::RZ:   std::cout << "[Rz ]--"; break;
                        case GateType::CNOT: std::cout << "[ X ]--"; break; // Target for CNOT
                    }
                } else if (op.control == i) {
                    std::cout << "[ * ]--";
                } else { std::cout << "-------"; }
            }
            std::cout << "[M]\n";
        }
        std::cout << "=======================\n";
    }
private:
    void execute_cpu() {
        for (const auto& op : operations) {
            if (op.type == GateType::H) {
                Tensor<T> temp(2, 2);
                size_t physical_target = num_qubits - 1 - op.target;

                for (size_t i = 0; i < num_qubits; ++i) {
                    Tensor<T> current_gate = (i == physical_target) ? Tensor<T>::Hadamard() : Tensor<T>::Identity();
                    if (i == 0) temp = current_gate;
                    else temp = temp.kronecker(current_gate);
                }
                state = temp * state;

            } else if (op.type == GateType::CNOT) {
                Tensor<T> op0(2, 2), op1(2, 2);
                size_t physical_control = num_qubits - 1 - op.control;
                size_t physical_target = num_qubits - 1 - op.target;

                for (size_t i = 0; i < num_qubits; ++i) {
                    Tensor<T> gate0 = (i == physical_control) ? Tensor<T>::P0() : Tensor<T>::Identity();
                    Tensor<T> gate1(2, 2);

                    if (i == physical_control) gate1 = Tensor<T>::P1();
                    else if (i == physical_target) gate1 = Tensor<T>::X();
                    else gate1 = Tensor<T>::Identity();

                    if (i == 0) {
                        op0 = gate0;
                        op1 = gate1;
                    } else {
                        op0 = op0.kronecker(gate0);
                        op1 = op1.kronecker(gate1);
                    }
                }
                state = (op0 + op1) * state;
            }
        }
    }

    void execute_cudaq(int shots) {
        auto kernel = cudaq::make_kernel();

        auto q = kernel.qalloc(num_qubits);

        for (const auto& op : operations) {
            switch (op.type) {
                case GateType::H:    kernel.h(q[op.target]); break;
                case GateType::CNOT: kernel.x<cudaq::ctrl>(q[op.control], q[op.target]); break;
                case GateType::X:    kernel.x(q[op.target]); break;
                case GateType::Y:    kernel.y(q[op.target]); break;
                case GateType::Z:    kernel.z(q[op.target]); break;
                case GateType::RX:   kernel.rx(op.angle, q[op.target]); break;
                case GateType::RY:   kernel.ry(op.angle, q[op.target]); break;
                case GateType::RZ:   kernel.rz(op.angle, q[op.target]); break;
            }
        }

        kernel.mz(q);
        auto counts = cudaq::sample(shots, kernel);

        for (auto& [bitstring, count] : counts) {
            double percentage = (count * 100.0) / shots;
            std::cout << "State |" << bitstring << "> : " << percentage << "%\n";
        }
    }
};

#endif //LINUXTEST_QUANTUMCIRCUIT_H
