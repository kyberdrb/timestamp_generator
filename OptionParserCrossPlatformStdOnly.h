//
// Created by laptop on 7/25/24.
//

#pragma once

#include <memory>
#include <unordered_map>

class Options;

class OptionParserCrossPlatformStdOnly {
//class OptionParserCrossPlatformStdOnly : public CommandLineArgumentsOptionsParser {
public:
//private:
    std::unique_ptr<Options> parseCommandLineArgumentsInCustomCPPstyleToOptions(int argc, char**& argv);

//public:
//    std::unique_ptr<Options> parseOptions(int argc_numberOfCommandLineArguments, char**& argv_valueOfCommandLineArguments) override;

private:
    std::unordered_map<std::string, std::string> parseCommandLineArguments(int argc, char* argv[], const std::unordered_map<std::string, bool>& optionsWithValues);

    void print_usage(const std::string& fullPathToBinaryAsString) const;
};
