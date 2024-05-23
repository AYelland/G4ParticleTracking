#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int main() {
    std::ifstream file("USStandardAtmosphere.dat"); // Replace example.txt with your file name

    if (!file.is_open()) {
        std::cerr << "Could not open the file." << std::endl;
        return 1;
    }

    std::string line;
    std::vector<std::string> altitude, density, pressure, temperature, molarWeight;

    std::getline(file, line); // Skip the first line
    while (std::getline(file, line)) {
        size_t pos = 0;
        std::string delimiter = "\t"; // Using tab as the delimiter

        for (int i = 0; i < 4; ++i) {
            pos = line.find(delimiter);
            std::string token = line.substr(0, pos);
            switch (i) {
                case 0:
                    altitude.push_back(token);
                    break;
                case 1:
                    density.push_back(token);
                    break;
                case 2:
                    pressure.push_back(token);
                    break;
                case 3:
                    temperature.push_back(token);
                    break;
                default:
                    break;
            }
            line.erase(0, pos + delimiter.length());
        }
        molarWeight.push_back(line); // Add the last token
    }

    // Print the data to verify it was read correctly
    for (size_t i = 0; i < altitude.size(); ++i) {
        std::cout << altitude[i] << "\t" << density[i] << "\t" << pressure[i] << "\t" << temperature[i] << "\t" << molarWeight[i] << std::endl;
    }

    file.close();

    return 0;
}
