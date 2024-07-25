//
// Created by laptop on 7/25/24.
//

#pragma once

#include "CommandLineArgumentsOptionsParser.h"

#include <memory>

class Options;

class OptionParserPosixOnlyViaGetopt {
//class OptionParserPosixOnlyViaGetopt : public CommandLineArgumentsOptionsParser {
public:
//private:
    std::unique_ptr<Options> parseCommandLineArgumentsInCstyleWithGetOptToOptions(int argc, char**& argv);

//public:
//    std::unique_ptr<Options> parseOptions(int argc_numberOfCommandLineArguments, char**& argv_valueOfCommandLineArguments) override;

private:
    void print_usage(const std::string& fullPathToBinaryAsString) const;
};
