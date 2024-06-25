#include "Timestamp.h"

#include "Options.h"

#include <iostream>
#include <memory>
#include <unordered_map>

void parseCommandLineArgumentsCPPstyle(int argc, char**& argv);
std::unique_ptr<Options> parseCommandLineArgumentsCPPstyleToOptions(int argc, char**& argv);
// Function to parse command-line arguments
std::unordered_map<std::string, std::string> parseCommandLineArguments(int argc, char* argv[], const std::unordered_map<std::string, bool>& optionsWithValues);

int main(int argc, char *argv[]) {
    parseCommandLineArgumentsCPPstyle(argc, argv);
//    std::cout << Timestamp::generate() << std::endl;

//    std::cout << Timestamp::generate(precision, disable_padding = false) << std::endl;

    std::unique_ptr<Options> options = parseCommandLineArgumentsCPPstyleToOptions(argc, argv);
    std::cout << Timestamp::generate(*options) << std::endl;
    return 0;
}

void parseCommandLineArgumentsCPPstyle(int argc, char**& argv) {
    // Define options and whether they expect a value
    std::unordered_map<std::string, bool> optionsWithValues = {
            {"p", true},
            {"precision", true},
            {"d", false},
            {"nopadding", false}
    };

    auto args = parseCommandLineArguments(argc, argv, optionsWithValues);

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

std::unique_ptr<Options> parseCommandLineArgumentsCPPstyleToOptions(int argc, char**& argv) {
    // Define options and whether they expect a value
    std::unordered_map<std::string, bool> commandLineoptionsWithValueDefinitionRequirement = {
            {"p", true},
            {"precision", true},
            {"d", false},
            {"nopadding", false}
    };

    auto args = parseCommandLineArguments(argc, argv, commandLineoptionsWithValueDefinitionRequirement);

    auto options = std::make_unique<Options>();

    // Example usage of parsed arguments
    if (args.find("p") != args.end() || args.find("precision") != args.end()) {
        std::string precision = args.find("p") != args.end() ? args["p"] : args["precision"];
#ifdef _DEBUG
        std::cout << "precision: " << precision << std::endl;
#endif
        options->setPrecision(std::move(precision));
    }

    if (args.find("d") != args.end() || args.find("nopadding") != args.end()) {
#ifdef _DEBUG
        std::cout << "nopadding: padding disabled" << std::endl;
#endif
        options->disablePadding();
    }

    return options;
}

// Function to parse command-line arguments
std::unordered_map<std::string, std::string> parseCommandLineArguments(int argc, char* argv[], const std::unordered_map<std::string, bool>& optionsWithValues) {
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
