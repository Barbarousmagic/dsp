#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <chrono>
#include <random>
#include "Tensor.h"

struct DataPoint {
    int time_ns;
    double voltage;
};

int main() {
    std::cout << "[SYSTEM] Tensor Engine Test Start...\n";
    Tensor A(2,2);
    A(0,0) = 1.0; A(0,1) = 2.0;
    A(1,0) = 3.0; A(1,1) = 4.0;

    Tensor B(2, 2);
    B(0,0) = 2.0; B(0,1) = 0.0;
    B(1,0) = 1.0; B(1,1) = 2.0;

     std::cout << "[INFO] Multiplying A * B...\n";
    Tensor C = A.matmul(B);
    std::cout << "--- Result Matrix C ---\n";
    std::cout << C(0,0) << "  " << C(0,1) << "\n";
    std::cout << C(1,0) << " " << C(1,1) << "\n";
    return 0;
}