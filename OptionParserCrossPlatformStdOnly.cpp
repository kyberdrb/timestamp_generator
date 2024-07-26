//
// Created by laptop on 7/25/24.
//

#include "OptionParserCrossPlatformStdOnly.h"

#include "Options.h"

#include <filesystem>
#include <iostream>
#include <unordered_map>

//std::unique_ptr<Options> OptionParserCrossPlatformStdOnly::parseOptions(int argc_numberOfCommandLineArguments, char**& argv_valueOfCommandLineArguments) override {
//    return parseOptions(argc_numberOfCommandLineArguments, argv_valueOfCommandLineArguments);
//}

std::unique_ptr<Options> OptionParserCrossPlatformStdOnly::parseCommandLineArgumentsInCustomCPPstyleToOptions(int argc, char**& argv) {
    // Define options and whether they expect a value
    std::unordered_map<std::string, bool> commandLineoptionsWithValueDefinitionRequirement = {
            {"p", true},
            {"precision", true},
            {"d", false},
            {"nopadding", false},
            {"?", false},
            {"help", false}
            // TODO add option [-f|--format] which will be forwarded to the Timestamp class' 'generate' function
    };

    auto args = this->parseCommandLineArguments(argc, argv, commandLineoptionsWithValueDefinitionRequirement);
    auto options = std::make_unique<Options>();

    // Example usage of parsed arguments
    if (args.find("p") != args.end() || args.find("precision") != args.end()) {
        std::string precision = args.find("p") != args.end() ? args["p"] : args["precision"];
#ifdef _DEBUG
        std::cout << "OptionParserCrossPlatformStdOnly: precision: " << precision << std::endl;
#endif
        options->setPrecision(precision);
    }

    if (args.find("d") != args.end() || args.find("nopadding") != args.end()) {
#ifdef _DEBUG
        std::cout << "OptionParserCrossPlatformStdOnly: nopadding: high precision remainder padding disabled" << std::endl;
#endif
        options->disablePadding();
    }

    if (args.find("?") != args.end() || args.find("help") != args.end()) {
#ifdef _DEBUG
        std::cout << "OptionParserCrossPlatformStdOnly: help invoked" << std::endl;
#endif
        this->print_usage(argv[0]);
    }

    return options;
}

// Function to parse command-line arguments
//  Essentially 'getopt' coded by hand
std::unordered_map<std::string, std::string> OptionParserCrossPlatformStdOnly::parseCommandLineArguments(int argc, char* argv[], const std::unordered_map<std::string, bool>& optionsWithValues) {
    std::unordered_map<std::string, std::string> arguments;

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];

        // TODO test options terminator "--" with each options parsing strategy
        if (arg == "--") {
#ifdef _DEBUG
            std::cout << "OptionParserCrossPlatformStdOnly: option terminator '--' detected - handling non-option command line arguments" << std::endl;
            // skip handling of nonoption command line arguments
            break;
#endif
        }

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
                    std::cerr << "OptionParserCrossPlatformStdOnly: Option '" << arg << "' requires a value" << std::endl;
                }
            }

            arguments[key] = value;
        }
    }

    return arguments;
}

// TODO encapsulate into separate class 'Help'
void OptionParserCrossPlatformStdOnly::print_usage(const std::string& fullPathToBinaryAsString) const {
    std::filesystem::path fullPathToBinary{fullPathToBinaryAsString};
    std::cout << "Usage: " << fullPathToBinary.filename().string() << " [-p|--precision] PRECISION [-d|--nopadding]" << std::endl;
}
