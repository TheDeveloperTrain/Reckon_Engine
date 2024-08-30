#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>

namespace fs = std::filesystem;

int CountLinesInFile(const fs::path& filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file " << filePath << std::endl;
        return 0;
    }

    int lineCount = 0;
    std::string line;
    while (std::getline(file, line)) {
        lineCount++;
    }

    return lineCount;
}

int CountLinesInDirectory(const fs::path& directoryPath) {
    int totalLines = 0;

    try {
        for (const auto& entry : fs::recursive_directory_iterator(directoryPath)) {
            // Normalize path to avoid case sensitivity issues
            if (entry.is_directory() && entry.path().filename().string() == "dependencies") {
                continue; // Skip the "dependencies" directory
            }

            if (entry.is_regular_file()) {
                const fs::path& filePath = entry.path();
                if (filePath.extension() == ".cpp" || filePath.extension() == ".h" || filePath.extension() == ".cs" || filePath.extension() == ".xaml") {
                    int lines = CountLinesInFile(filePath);
                    std::cout << "File: " << filePath << " - " << lines << " lines" << std::endl;
                    totalLines += lines;
                }
            }
        }
    }
    catch (const fs::filesystem_error& e) {
        std::cerr << "Filesystem error: " << e.what() << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "General error: " << e.what() << std::endl;
    }

    return totalLines;
}

int main() {

    fs::path pathToSearch("D:\\Reckon Engine\\Reckon Engine\\Reckon Extras clone without dependencies");

    if (!fs::exists(pathToSearch) || !fs::is_directory(pathToSearch)) {
        std::cerr << "Error: Invalid directory path." << std::endl;
        return 1;
    }

    int totalLines = CountLinesInDirectory(pathToSearch);
    std::cout << "Total lines of code in Reckon Engine: " << totalLines << std::endl;
    return 0;
}
