//
// Created by laptop on 6/14/24.
//

#include "IDGenerator.h"

#include <chrono>
#include <iomanip>

#ifdef _DEBUG
#include <cassert>
#include <iostream>
#endif

std::mutex IDGenerator::idGeneratorMutex;

/// @brief Generates timestamp
/// @return timestamp with given precision
std::string IDGenerator::generateTimestamp() {
    std::lock_guard<std::mutex> lock(IDGenerator::idGeneratorMutex);

    auto currentTime = std::chrono::system_clock::now();
    auto currentCalendarTime = std::chrono::system_clock::to_time_t(currentTime);
    auto currentLocalCalendarTime = std::localtime(&currentCalendarTime);
    std::stringstream timestamp;
    timestamp << std::put_time(currentLocalCalendarTime, "%Y%m%d%H%M%S");
#ifdef _DEBUG
    std::cout << timestamp.str() << std::endl;
#endif

    auto timeSinceEpoch = currentTime.time_since_epoch();
#ifdef _DEBUG
    assert(timeSinceEpoch.count() == currentTime.time_since_epoch().count());
#endif

    auto microsecondsSinceEpoch = std::chrono::duration_cast<std::chrono::microseconds>(timeSinceEpoch);
#ifdef _DEBUG
    std::cout << microsecondsSinceEpoch.count() << std::endl;
#endif

    auto secondsSinceEpoch = std::chrono::duration_cast<std::chrono::seconds>(timeSinceEpoch);
#ifdef _DEBUG
    std::cout << secondsSinceEpoch.count() << std::endl;
#endif

    auto tailTime /*chvostikovy cas*/ = microsecondsSinceEpoch - secondsSinceEpoch;
#ifdef _DEBUG
    std::cout << tailTime.count() << std::endl;
#endif

    std::stringstream remainder;

    // align the time difference to 6 (six) digits = milliseconds precision (3 digits) + microseconds precision (3 digits)
    //   because milli-, micro- and nanoseconds have each 3 digits precision
    //   thus when the precision is set to microseconds, the number of tail time digits is cumulative
    //  and pad missing digits with '0' (zeros)
    // TODO align according to precision
    //  - milliseconds -> 3 chars width
    //  - microseconds -> 6 chars width
    //  -  nanoseconds -> 9 chars width
    remainder << std::setw(6) << std::setfill('0');
    remainder << tailTime.count();

#ifdef _DEBUG
    remainder.str("");
    remainder.clear();

    // ↓↓ for debug purposes to test the padding
    //auto currentTimeMicrosecondsRemainder = 0;
    //auto currentTimeMicrosecondsRemainder = 1;
    auto currentTimeMicrosecondsRemainder = 12;
    //auto currentTimeMicrosecondsRemainder = 123;
    //auto currentTimeMicrosecondsRemainder = 1234;
    //auto currentTimeMicrosecondsRemainder = 12345;
    // ^^ for testing and debug purposes

    std::cout << currentTimeMicrosecondsRemainder << std::endl;

    // either...
    // remainder << std::setw(6) << std::setfill('0') << "123"; // for testing and debug purposes
    //assert(3 == remainder.str().length()); // code like yoda

    // ...or
    remainder << std::setw(6) << std::setfill('0') << currentTimeMicrosecondsRemainder;
    std::cout << remainder.str() << " : " << remainder.str().length() << std::endl;
    assert(6 == remainder.str().length()); // code like yoda

    std::cout << timestamp.str() << std::endl;
    std::cout << timestamp.str() << currentTimeMicrosecondsRemainder << std::endl;
    std::cout << timestamp.str() << remainder.str() << std::endl;
    assert(20 == timestamp.str().length() + remainder.str().length()); // code like yoda
#endif

    timestamp << remainder.str();
    return timestamp.str();
}
