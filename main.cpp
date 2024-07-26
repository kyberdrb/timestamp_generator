#include "Timestamp.h"

#include "CommandLineArgumentsOptionsParser.h"
#include "OptionParserPosixOnlyViaGetopt.h"
#include "OptionParserCrossPlatformStdOnly.h"
#include "Options.h"

#include <iostream>

int main(int argc, char *argv[]) {
    auto optionParserPosixOnlyViaGetopt = std::make_unique<OptionParserPosixOnlyViaGetopt>();
    auto optionsFromGetoptParser = optionParserPosixOnlyViaGetopt->parseCommandLineArgumentsInCstyleWithGetOptToOptions(argc, argv);

    // TODO use strategy design pattern to parse optionsFromGetoptParser from command line arguments: select one of them randomly - or first one, then the other - and then compare 'Options' instances for equality
//    std::unique_ptr<CommandLineArgumentsOptionsParser> optionParserPosixOnlyViaGetopt = std::make_unique<OptionParserPosixOnlyViaGetopt>();
//    auto optionsFromGetoptParser = optionParserPosixOnlyViaGetopt->parseCommandLineArguments(argc, argv);
    auto timestamp = Timestamp::generate(*optionsFromGetoptParser);
    std::cout << timestamp << std::endl;

    auto optionParserCrossPlatformStdOnly = std::make_unique<OptionParserCrossPlatformStdOnly>();
    auto optionsFromStdOnlyParser = optionParserCrossPlatformStdOnly->parseCommandLineArgumentsInCustomCPPstyleToOptions(argc, argv);
    // TODO same here
//    std::unique_ptr<CommandLineArgumentsOptionsParser> optionParserCrossPlatformStdOnly = std::make_unique<OptionParserCrossPlatformStdOnly>();
//    auto optionsFromStdOnlyParser = optionParserCrossPlatformStdOnly->parseCommandLineArguments(argc, argv);

    // TODO add option '-t'/'--trim-trailing-zeros' from remainder: effective only for option 'precision' with values 'milli/micro/nanoseconds'
    // TODO add option '-f'/'--format' to change the base timestamp: will work alone or with combination with the option  'precision' with values 'milli/micro/nanoseconds' to add high precision remainder values
    return 0;
}
