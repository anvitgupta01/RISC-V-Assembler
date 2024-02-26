#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <map>
using namespace std;

int main() {
    // Open the input assembly file for reading.
    std::ifstream inputFile("Assembley.asm");

    if (!inputFile.is_open()) {
        std::cerr << "Unable to open input file." << std::endl;
        return 1;
    }

    // Open the output assembly file for writing.
    std::ofstream outputFile("Outyi.asm");

    if (!outputFile.is_open()) {
        std::cerr << "Unable to open output file." << std::endl;
        return 1;
    }

    std::string line;
    std::map<std::string, int> labelMap;  // Map to store label names and their line numbers

    int lineNumber = 0;
    while (std::getline(inputFile, line)) {
        // Remove comments (lines starting with '#').
        line = std::regex_replace(line, std::regex("#.*"), "");

        // Check if the line contains a label (lines ending with ':' followed by optional whitespace).
        std::smatch labelMatch;
        if (std::regex_search(line, labelMatch, std::regex("^\\s*([a-zA-Z_][a-zA-Z_0-9]*)\\s*:"))) {
            // If a label is found, add it to the label map with the current line number.
            labelMap[labelMatch[1].str()] = lineNumber + 1; // Start line numbers from 1.
        } else {
            // If there's no label, remove leading and trailing whitespace.
            line = std::regex_replace(line, std::regex("^\\s+|\\s+$"), "");

            // Write the modified line (with assembly code) to the output file.
            if (!line.empty()) {
                outputFile << line << std::endl;
            }
        }

        lineNumber++;
    }

    for (const auto& pair : labelMap) {
        std::cout << "Label: " << pair.first << " at line: " << pair.second << std::endl;
    }

    inputFile.close();
    outputFile.close();


    return 0;
}
