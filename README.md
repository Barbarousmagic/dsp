# Quantum Hardware DSP Framework

A high-performance, memory-optimized C++ toolset for digital signal processing and quantum state simulation.

## Overview
This project focuses on the low-level systemic challenges of scaling quantum hardware. It provides tools to simulate quantum entanglement and process highly noisy datasets typical for cryogenic readouts (e.g., Charge Stability Diagrams for Spin Qubits).

The architecture is split into modular executables, demonstrating hardware-aware programming, cache optimization, and multithreading.

## Modules

### 1. 2D Charge Stability Diagram (CSD) Filtering
Simulates the measurement of quantum dot charge transitions under extreme cryogenic noise (low SNR).
- Applies a custom 2D Convolution Filter (Moving Average) to smooth Gaussian white noise.
- Prepares data for Automated Tuning Solutions by extracting sharp charge transition boundaries.

### 2. Cache-Friendly Tensor Engine & Quantum Entanglement
A custom mathematical engine built from scratch to simulate quantum logic gates and qubit interactions.
- **Cache Optimization:** Matrix multiplication (`matmul`) algorithms are optimized for CPU cache lines to prevent Cache Misses during intensive calculations.
- **Quantum Simulation:** Successfully computes the Kronecker product for multi-qubit systems, simulating the Hadamard gate and CNOT to generate maximally entangled Bell states ($\beta_{00}$).

### 3. High-Throughput 1D DSP Pipeline
Generates and filters millions of samples of Gaussian noise to test single-thread and OpenMP multi-thread limits.
- Validates data streams simulating quantum hardware readout electronics.

## Technical Highlights
- **Hardware-Aware C++:** Strict control over memory layout, loop indexing, and heap fragmentation (`std::vector::reserve`).
- **Parallel Computing:** Integrates OpenMP for processing large data arrays.
- **Robust I/O:** Safe data streams and terminal-friendly outputs for debugging and visualization.