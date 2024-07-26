//
// Created by laptop on 7/25/24.
//

#include "OptionParserPosixOnlyViaGetopt.h"

#include "Options.h"

#include <filesystem>
#include <getopt.h>
#include <iostream>

//std::unique_ptr<Options> OptionParserPosixOnlyViaGetopt::parseOptions(int argc_numberOfCommandLineArguments, char**& argv_valueOfCommandLineArguments) override {
//    return this->parseCommandLineArgumentsInCstyleWithGetOptToOptions(argc_numberOfCommandLineArguments, argv_valueOfCommandLineArguments);
//}

std::unique_ptr<Options> OptionParserPosixOnlyViaGetopt::parseCommandLineArgumentsInCstyleWithGetOptToOptions(int argc, char**& argv) {
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
                std::cout << "nopadding: high precision remainder padding disabled" << std::endl;
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

void OptionParserPosixOnlyViaGetopt::print_usage(const std::string& fullPathToBinaryAsString) const {
    std::filesystem::path fullPathToBinary{fullPathToBinaryAsString};
    std::cout << "Usage: " << fullPathToBinary.filename().string() << " [-p|--precision] PRECISION [-d|--nopadding]" << std::endl;
}
