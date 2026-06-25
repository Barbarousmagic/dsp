# Quantum Noise DSP Filter

A fast, memory-optimized C++ prototype for digital signal processing. 

## Overview
This project simulates the extraction of a useful signal from a highly noisy environment, typical for quantum hardware readouts (e.g., retrieving qubit states from a cryostat). 

It generates a dataset of raw Gaussian noise and applies a custom Moving Average filter to smooth the data, outputting the results into CSV format for further visualization.

## Technical Highlights
- **Modern C++:** Utilizes aggregate initialization and range-based `const auto&` loops for safe data iteration.
- **Memory Optimization:** Prevents heap fragmentation and allocation overhead by pre-calculating and reserving vector memory `std::vector::reserve()`.
- **Data Pipeline:** Implements robust I/O streams (`std::ifstream` / `std::ofstream`) with error handling to prevent silent segmentation faults.
- **CLI Visualization:** Compatible with terminal-based plotting tools like `gnuplot` for instant ASCII data rendering.
