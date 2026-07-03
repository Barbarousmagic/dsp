//
// Created by novod on 02.07.2026.
//

#ifndef LINUXTEST_QUANTUMCIRCUIT_H
#define LINUXTEST_QUANTUMCIRCUIT_H

#include <vector>
#include "Tensor.h"
template <typename T>
class QuantumCircuit {
private:
    size_t num_qubits;
    Tensor<T> state;
public:
    QuantumCircuit(size_t qubits) : num_qubits(qubits), state(1 << qubits, 1) {
        state(0, 0) = T{1.0}; // start state |00...0>
    }
    void print_state() const {
        state.print();
    }

    void h(size_t target) {
        Tensor<T> temp(2, 2);
        for (size_t i = 0; i < num_qubits; ++i) {
            Tensor<T> current_gate = (i == target) ? Tensor<T>::Hadamard() : Tensor<T>::Identity();
            if (i == 0) temp = current_gate;
            else temp = temp.kronecker(current_gate);
        }
        state = temp * state;
    }
};

#endif //LINUXTEST_QUANTUMCIRCUIT_H
