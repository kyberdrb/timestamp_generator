#include "Timestamp.h"

#include "Options.h"

#include <filesystem>
#include <iostream>
#include <memory>
#include <unordered_map>
#include <getopt.h>

std::unique_ptr<Options> parseCommandLineArgumentsInCustomCPPstyleToOptions(int argc, char**& argv);
// Function to parse command-line arguments
std::unordered_map<std::string, std::string> parseCommandLineArguments(int argc, char* argv[], const std::unordered_map<std::string, bool>& optionsWithValues);
std::unique_ptr<Options> parseCommandLineArgumentsInCstyleWithGetOptToOptions(int argc, char**& argv);

void print_usage(const std::string& fullPathToBinaryAsString);

int main(int argc, char *argv[]) {
    // TODO use strategy design pattern to parse options from command line arguments: switch between them randomly and then compare 'Options' instances for equality
//    std::unique_ptr<Options> options = parseCommandLineArgumentsInCustomCPPstyleToOptions(argc, argv);
    std::unique_ptr<Options> options = parseCommandLineArgumentsInCstyleWithGetOptToOptions(argc, argv);

    std::cout << Timestamp::generate(*options) << std::endl;
    return 0;
}

std::unique_ptr<Options> parseCommandLineArgumentsInCustomCPPstyleToOptions(int argc, char**& argv) {
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

    auto args = parseCommandLineArguments(argc, argv, commandLineoptionsWithValueDefinitionRequirement);
    auto options = std::make_unique<Options>();

    // Example usage of parsed arguments
    if (args.find("p") != args.end() || args.find("precision") != args.end()) {
        std::string precision = args.find("p") != args.end() ? args["p"] : args["precision"];
#ifdef _DEBUG
        std::cout << "parse: precision: " << precision << std::endl;
#endif
        options->setPrecision(precision);
    }

    if (args.find("d") != args.end() || args.find("nopadding") != args.end()) {
#ifdef _DEBUG
        std::cout << "parse: nopadding: padding disabled" << std::endl;
#endif
        options->disablePadding();
    }

    return options;
}

// Function to parse command-line arguments
//  Essentially 'getopt' coded by hand
std::unordered_map<std::string, std::string> parseCommandLineArguments(int argc, char* argv[], const std::unordered_map<std::string, bool>& optionsWithValues) {
    std::unordered_map<std::string, std::string> arguments;

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];

        // TODO test options terminator "--" with each options parsing strategy
        if (arg == "--") {
#ifdef _DEBUG
            std::cout << "option terminator '--' detected - handling non-option command line arguments" << std::endl;
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
                    std::cerr << "Option '" << arg << "' requires a value" << std::endl;
                }
            }

            arguments[key] = value;
        }
    }

    return arguments;
}

std::unique_ptr<Options> parseCommandLineArgumentsInCstyleWithGetOptToOptions(int argc, char**& argv) {
    auto options = std::make_unique<Options>();

    int option = -1;

    struct option long_options[] = {
            {"precision", required_argument, nullptr, 'p'}, // when 'required_argument' has an empty value, the 'getopt_long' prints error message 'option requires an argument -- 'p''
            {"nopadding", no_argument, nullptr, 'd'},
            {"help", no_argument, nullptr, '?'},
            {nullptr, 0, nullptr, 0}
    };

    int option_index = 0;

    while ((option = getopt_long(
            argc,
            argv,
            "p:d?", // all available short/single-letter options need to be listed here to prevent error "invalid option -- '?'"
            long_options,
            &option_index)) != -1)
    {
        switch (option) {
            case 'p': {
                std::string precisionValue = optarg;
#ifdef _DEBUG
                std::cout << "precision: " << precisionValue << std::endl;
#endif
                options->setPrecision(precisionValue);
                break;
            }
            case 'd':
#ifdef _DEBUG
                std::cout << "nopadding: padding disabled" << std::endl;
#endif
                options->disablePadding();
                break;
            case '?':
#ifdef _DEBUG
                std::cout << "help invoked" << std::endl;
#endif
                print_usage(argv[0]);
                break;
            default:
#ifdef _DEBUG
                std::cerr << "Unknown option: " << option << std::endl;
#endif
                print_usage(argv[0]);
                break;
        }
    }

    return options;
}

void print_usage(const std::string& fullPathToBinaryAsString) {
    std::filesystem::path fullPathToBinary{fullPathToBinaryAsString};
    std::cout << "Usage: " << fullPathToBinary.filename().string() << " [-p|--precision] PRECISION [-d|--nopadding]" << std::endl;
}
