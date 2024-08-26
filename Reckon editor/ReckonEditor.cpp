#include "ReckonEditor.h"
#include <filesystem>
#include <fstream>
#include "ReckonConfig.h"
#include <imgui.h>
#include <iostream> 
#include <algorithm>
// Constants
constexpr size_t MaxInputLength = 64; // Maximum length for input text

std::string ReadFileToString(const std::string& path);
void WriteStringToFile(const std::string& path, const std::string& content);
template <typename T>
void AddElementIfUnique(std::vector<T>& vector, const T& value);
std::string ExtractLayoutName(std::string path);

void ReckonEditor::InitWorkingDirectories()
{
    if (!std::filesystem::is_directory("Editor Saves"))
    {
        std::filesystem::create_directory("Editor Saves");
    }
    if (!std::filesystem::is_directory("Editor Saves/Layouts"))
    {
        std::filesystem::create_directory("Editor Saves/Layouts");
    }
}

void ReckonEditor::SaveLayoutPathFile()
{
    if (!std::filesystem::is_directory("Editor Saves"))
    {
        throw std::runtime_error("Editor Saves directory not yet initialized");
    }
    std::ofstream layoutFile("Editor Saves/LayoutData.txt");
    for (auto& path : ReckonConfig::layoutFilePaths)
    {
        layoutFile << path << std::endl;
    }
}

void ReckonEditor::LoadLayoutPathFile() {
    std::ifstream inFile("Editor Saves/LayoutData.txt");
    if (!inFile) {
        std::cerr << "Failed to open LayoutData.txt for reading!" << std::endl;
        return;
    }
    std::string path;
    while (std::getline(inFile, path)) {
        if (std::filesystem::exists(path)) {
            ReckonConfig::layoutFilePaths.push_back(path);
            ReckonConfig::layoutNames.push_back(ExtractLayoutName(path));
        }
    }
}
void ReckonEditor::SaveLayoutWithName(const char* name)
{
    if (!std::filesystem::is_directory("Editor Saves/Layouts"))
    {
        throw std::runtime_error("Layout directory not yet initialized");
    }

    std::string layoutName(name);
    if (layoutName.empty())
    {
        std::cerr << "Error: Layout name cannot be empty." << std::endl;
        return;
    }

    std::string currentLayoutString = ReadFileToString("imgui.ini");
    if (currentLayoutString.empty())
    {
        std::cerr << "Warning: imgui.ini file is empty or could not be read." << std::endl;
        return;
    }

    std::string savePath = "Editor Saves/Layouts/" + layoutName + ".ini";
    WriteStringToFile(savePath, currentLayoutString);

    if (!std::filesystem::exists(savePath))
    {
        std::cerr << "Error: Failed to save layout to " << savePath << std::endl;
    }
    else
    {
        AddElementIfUnique(ReckonConfig::layoutFilePaths, savePath);
        AddElementIfUnique(ReckonConfig::layoutNames, ExtractLayoutName(savePath));
    }
}

void ReckonEditor::LoadLayoutWithName(const std::string& name)
{

    // Check if the layout file exists
    if (!std::filesystem::exists(name))
    {
        throw std::runtime_error("Layout file does not exist.");
    }

    // Load the layout from the ini file
    ImGui::LoadIniSettingsFromDisk(name.c_str());
}

void ReckonEditor::ClearLayoutData()
{
    ReckonConfig::layoutFilePaths.clear();
    ReckonConfig::layoutNames.clear();
    std::ofstream layoutFile("Editor Saves/LayoutData.txt", std::ios::trunc);
    if (layoutFile.is_open())
    {
        layoutFile.close();
    }
}


//-------------------------Helper Functions-------------------------------

std::string ReadFileToString(const std::string& path)
{
    std::ifstream inputFile(path);
    if (!inputFile.is_open())
    {
        std::cerr << "Error: Unable to open file " << path << std::endl;
        return "";
    }

    std::string output;
    std::string line;
    while (std::getline(inputFile, line))
    {
        output += line + "\n"; // Add newline to preserve original file structure
    }
    return output;
}

void WriteStringToFile(const std::string& path, const std::string& content)
{
    std::ofstream outFile(path);
    if (!outFile)
    {
        std::cerr << "Error: Unable to open file " << path << " for writing." << std::endl;
        return;
    }
    outFile << content;
}

template <typename T>
void AddElementIfUnique(std::vector<T>& vector, const T& value)
{
    if (std::find(vector.begin(), vector.end(), value) == vector.end())
    {
        vector.push_back(value);
    }
}

std::string ExtractLayoutName(std::string path)
{
    int startingIndex = 21;
    int endingIndex = (path.length() - 4) - 21;
    return path.substr(startingIndex, endingIndex);
}