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
        size_t physical_target = num_qubits - 1 - target;
        for (size_t i = 0; i < num_qubits; ++i) {
            Tensor<T> current_gate = (i == physical_target) ? Tensor<T>::Hadamard() : Tensor<T>::Identity();
            if (i == 0) temp = current_gate;
            else temp = temp.kronecker(current_gate);
        }
        state = temp * state;
    }

    void cnot(size_t control, size_t target) {
        Tensor<T> op0(2, 2), op1(2, 2);
        size_t physical_control = num_qubits - 1 - control;
        size_t physical_target = num_qubits - 1 - target;
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
};

#endif //LINUXTEST_QUANTUMCIRCUIT_H
