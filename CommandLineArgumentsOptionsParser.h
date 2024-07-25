//
// Created by laptop on 7/25/24.
//

#pragma once

#include <memory>

class Options;

class CommandLineArgumentsOptionsParser {
public:
    virtual std::unique_ptr<Options> parseOptions(int argc_numberOfCommandLineArguments, char**& argv_valueOfCommandLineArguments);
    virtual ~CommandLineArgumentsOptionsParser() = 0;
};
