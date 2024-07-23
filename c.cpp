#include <iostream>
#include <fstream>
#include <string>
#include <sys/stat.h>
#include <filesystem>

namespace fs = std::filesystem;

void createFile(const std::string& filename) {
    std::ofstream outfile(filename);
    if (outfile.is_open()) {
        std::cout << "File '" << filename << "' created successfully." << std::endl;
        outfile.close();
    } else {
        std::cerr << "Error creating file '" << filename << "'." << std::endl;
    }
}

void createDirectory(const std::string& dirname) {
    fs::path dirPath = fs::path("dirs") / dirname;
    if (fs::create_directories(dirPath)) {
        std::cout << "Directory '" << dirPath << "' created successfully." << std::endl;
    } else {
        std::cerr << "Error creating directory '" << dirPath << "'." << std::endl;
    }
}

int main() {
    std::string inputFilePath = "xss-payload-list.txt";
    std::ifstream inputFile(inputFilePath);
    std::string line;

    // Create "dirs" folder if it doesn't exist
    if (!fs::exists("dirs")) {
        if (!fs::create_directory("dirs")) {
            std::cerr << "Error creating base directory 'dirs'." << std::endl;
            return 1;
        }
    }

    if (inputFile.is_open()) {
        while (std::getline(inputFile, line)) {
            // Strip leading/trailing whitespace characters
            line.erase(0, line.find_first_not_of(" \t\n\r"));
            line.erase(line.find_last_not_of(" \t\n\r") + 1);

            if (!line.empty()) {
                if (line.back() == '/') { // Assume directory names end with '/'
                    line.pop_back();
                    createDirectory(line);
                } else {
                    createFile(line);
                }
            }
        }
        inputFile.close();
    } else {
        std::cerr << "Unable to open file '" << inputFilePath << "'." << std::endl;
        return 1;
    }

    return 0;
}

