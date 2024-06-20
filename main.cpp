#include "IDGenerator.h"

#include <iostream>
//#include <memory>
#include <unordered_map>

void parseArgumentsCPPstyle(int argc, char**& argv);
// Function to parse command-line arguments
std::unordered_map<std::string, std::string> parseArguments(int argc, char* argv[], const std::unordered_map<std::string, bool>& optionsWithValues);

int main(int argc, char *argv[]) {
    parseArgumentsCPPstyle(argc, argv);
    std::cout << IDGenerator::generateTimestamp() << std::endl;

//    std::unique_ptr<Arguments> arguments = parseArgumentsCPPstyle(argc, argv);
//    std::cout << IDGenerator::generateTimestamp(arguments) << std::endl;
    return 0;
}

void parseArgumentsCPPstyle(int argc, char**& argv) {
    // Define options and whether they expect a value
    std::unordered_map<std::string, bool> optionsWithValues = {
            {"p", true},
            {"precision", true},
            {"d", false},
            {"nopadding", false}
    };

    auto args = parseArguments(argc, argv, optionsWithValues);

    // Example usage of parsed arguments
    if (args.find("p") != args.end() || args.find("precision") != args.end()) {
        std::string precision = args.find("p") != args.end() ? args["p"] : args["precision"];
#ifdef _DEBUG
        std::cout << "precision: " << precision << std::endl;
#endif
    }

    if (args.find("d") != args.end() || args.find("nopadding") != args.end()) {
#ifdef _DEBUG
        std::cout << "nopadding: padding disabled" << std::endl;
#endif
    }
}

// Function to parse command-line arguments
std::unordered_map<std::string, std::string> parseArguments(int argc, char* argv[], const std::unordered_map<std::string, bool>& optionsWithValues) {
    std::unordered_map<std::string, std::string> arguments;

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];

        if (arg[0] == '-') {
            std::string key;
            std::string value;

            if (arg[1] == '-') {
                // Handle keyword arguments (e.g., --precision, --padding)
                key = arg.substr(2);
            } else {
                // Handle single-letter arguments (e.g., -p, -d)
                key = arg.substr(1);
            }

            // Check if this option expects a value
            if (optionsWithValues.find(key) != optionsWithValues.end() && optionsWithValues.at(key)) {
                if (i + 1 < argc && argv[i + 1][0] != '-') {
                    value = argv[++i];
                } else {
                    std::cerr << "Option '" << arg << "' requires a value" << std::endl;
                }
            }

            arguments[key] = value;
        }
    }

    return arguments;
}
