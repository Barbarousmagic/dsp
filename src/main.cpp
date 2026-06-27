#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <chrono>
#include <random>

struct DataPoint {
    int time_ns;
    double voltage;
};

int main() {
    const size_t NUM_SAMPLES = 50'000'000;
    std::cout << "[SYSTEM] Generating " << NUM_SAMPLES << " samples...\n";
    std::vector<DataPoint> signal_data;
    signal_data.resize(NUM_SAMPLES);
    std::mt19937 gen(1337);
    std::normal_distribution<double> noise_dist(0.0, 5.0);
    for (size_t i = 0; i < NUM_SAMPLES; ++i) {
        signal_data[i].time_ns = i * 10;
        signal_data[i].voltage = noise_dist(gen);
    }
    std::cout << "[SUCCESS] Array generation complete\n";

    std::vector<DataPoint> filtered_data;
    filtered_data.resize(signal_data.size());

    auto start_time = std::chrono::high_resolution_clock::now();

#pragma omp parallel for
    for (size_t i = 2; i < signal_data.size(); ++i) {
        double filtered_voltage = (signal_data[i-2].voltage + signal_data[i-1].voltage + signal_data[i].voltage) / 3.0;
        filtered_data[i].time_ns = signal_data[i].time_ns;
        filtered_data[i].voltage = filtered_voltage;
    }
    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
    std::cout << "[PERF] Parallel filtration took: " << duration.count() << " microseconds\n";
    std::cout << "[SUCCESS] Filtration ended. Lines: "
              << filtered_data.size() << "\n";
    std::ofstream file_out("qubit_filtered_data.csv");
    if (!file_out.is_open()) {
        std::cerr << "[ERROR] File not found!\n";
        return 1;
    }
    //file_out << "time_ns,voltage_mV\n";
    //for (size_t i = 2; i < filtered_data.size(); ++i) {
    //    file_out << filtered_data[i].time_ns << "," << filtered_data[i].voltage << "\n";
    //}
    file_out.close();

    double max_voltage = filtered_data[0].voltage;
    for (const auto& point : filtered_data) {
        if (point.voltage > max_voltage) max_voltage = point.voltage;
    }
    std::cout << max_voltage << "\n";
    return 0;
}