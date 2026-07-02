#include <cassert>
#include <cmath>
#include <chrono>
#include "Tensor.h"

int main() {
    std::cout << "===================================================\n";
    std::cout << "     RUNNING TEMPLATE TENSOR ALL METHODS TEST\n";
    std::cout << "===================================================\n";
    // 1. initialization and indexing
    std::cout << "[Test 1] Initialization and Indexing...\n";
    Tensor<double> A(2, 3);
    A(0, 0) = 1.0; A(0, 1) = 2.0; A(0, 2) = 3.0;
    A(1, 0) = 4.0; A(1, 1) = 5.0; A(1, 2) = 6.0;
    std::cout << "Matrix A(2x3):\n";
    A.print();
    std::cout << "Passed.\n\n";

    // 2. Adding test(add)
    std::cout << "[Test 2] Matrix addition...\n";
    Tensor<double> B(2, 3);
    B(0, 0) = 0.5; B(0, 1) = 1.5; B(0, 2) = 2.5;
    B(1, 0) = 3.5; B(1, 1) = 4.5; B(1, 2) = 5.5;
    Tensor<double> C = A + B;
    std::cout << "Matrix A + B:\n";
    C.print();
    assert(C(0, 0) == 1.5 && C(1, 2) == 11.5);
    std::cout << "Passed\n\n";

    // 3. Transpose test
    std::cout << "[Test 3] Matrix transpose...\n";
    Tensor<double> A_T = A.transpose();
    std::cout << "Matrix A^T (3x2):\n";
    A_T.print();
    assert(A_T.get_rows() == 3 && A_T.get_cols() == 2);
    assert(A_T(2, 1) == 6.0);
    std::cout << "Passed\n\n";

    //4. Kronecker product test
    std::cout << "[Test 4] Kronecker product...\n";
    Tensor<double> I2 = Tensor<double>::Identity();
    Tensor<double> X2 = Tensor<double>::X();
    Tensor<double> kron_res = I2.kronecker(X2);
    std::cout << "Identity (2x2) Kronecker Pauli-X (2x2):\n";
    kron_res.print();
    assert(kron_res.get_rows() == 4 && kron_res.get_cols() == 4);
    assert(kron_res(0, 1) == 1.0 && kron_res(2, 3) == 1.0);
    std::cout << "Passed\n\n";

    // 5. Inverse and basis change test
    std::cout << "[Test 5] Matrix inversion (Gauss-Jordan)...\n";
    Tensor<double> M(2, 2);
    M(0, 0) = 4.0; M(0, 1) = 7.0;
    M(1, 0) = 2.0; M(1, 1) = 6.0;
    std::cout << "Matrix M:\n";
    M.print();
    Tensor<double> M_inv = M.inverse();
    std::cout << "Matrix M^-1:\n";
    M_inv.print();

    //check: M * M^-1 should be close to I
    Tensor<double> E = M * M_inv;
    E.print();
    assert(std::abs(E(0, 0) - 1.0) < 1e-9 && std::abs(E(0, 1)) < 1e-9);
    std::cout << "Passed\n\n";

    // 6. Multiplication benchmark
    std::cout << "[Test 6] Benchmarking matmul vs matmul_slow (1000x1000)...\n";
    Tensor<double> BigA(1000, 1000);
    Tensor<double> BigB(1000, 1000);
    for (size_t i = 0; i < 1000; ++i) {
        BigA(i, i) = 2.0;
        BigB(i, i) = 0.5;
    }

    auto start_slow = std::chrono::high_resolution_clock::now();
    Tensor<double> slow_res = BigA.matmul_slow(BigB);
    auto finish_slow = std::chrono::high_resolution_clock::now();
    auto duration_slow = std::chrono::duration_cast<std::chrono::microseconds>(finish_slow - start_slow);
    std::cout << "Duration of slow method (i-j-k): " << duration_slow.count() << " mcs\n";
    auto start_fast = std::chrono::high_resolution_clock::now();
    Tensor<double> fast_res = BigA.matmul(BigB);
    auto finish_fast = std::chrono::high_resolution_clock::now();
    auto duration_fast = std::chrono::duration_cast<std::chrono::microseconds>(finish_fast - start_fast);
    std::cout << "Duration of fast method (i-k-j): " << duration_fast.count() << " mcs\n";

    std::cout << "Performance difference: " << (double(duration_slow.count() - duration_fast.count()) / duration_slow.count()) * 100.0 << "%\n";
    std::cout << "Passed\n\n";

    std::cout << "===================================================\n";
    std::cout << "   ALL TESTS PASSED SUCCESSFULLY!\n";
    std::cout << "===================================================\n";
    return 0;
}