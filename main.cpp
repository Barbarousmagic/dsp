#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

struct DataPoint {
    int time_ns;
    double voltage;
};

int main() {
    std::cout << "[SYSTEM] Start... \n";
    std::ifstream file("qubit_noise_data.csv");
    if (!file.is_open()) {
        std::cerr << "[ERROR] File not found!\n";
        return 1;
    }
    std::vector<DataPoint> signal_data;
    std::string line;
    std::getline(file, line);
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string time_str, volt_str;

        std::getline(ss, time_str, ',');
        std::getline(ss, volt_str, ',');

        DataPoint current_point;
        current_point.time_ns = std::stoi(time_str);
        current_point.voltage = std::stod(volt_str);

        signal_data.push_back(current_point);
    }
    file.close();
    std::cout << "[SUCCESS] Data sind im RAM. Große des Vektors: "
              << signal_data.size() << " samples\n";

    std::vector<DataPoint> filtered_data;
    filtered_data.reserve(signal_data.size());
    for (size_t i = 2; i < signal_data.size(); ++i) {
        double filtered_voltage = (signal_data[i-2].voltage + signal_data[i-1].voltage + signal_data[i].voltage) / 3.0;
        DataPoint filtered_point{signal_data[i].time_ns, filtered_voltage};
        filtered_data.push_back(filtered_point);
    }
    std::cout << "[SUCCESS] Фильтрация завершена. Очищено сэмплов: "
              << filtered_data.size() << "\n";
    std::ofstream file_out("qubit_filtered_data.csv");
    if (!file_out.is_open()) {
        std::cerr << "[ERROR] File not found!\n";
        return 1;
    }
    file_out << "time_ns,voltage_mV\n";
    for (const auto& point : filtered_data) {
        file_out << point.time_ns << "," << point.voltage << "\n";
    }
    file_out.close();

    return 0;
}