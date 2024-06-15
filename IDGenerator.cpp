//
// Created by laptop on 6/14/24.
//

#include "IDGenerator.h"

#include <chrono>
#include <iomanip>

#ifdef _DEBUG
#include <cassert>
#endif
#include <iostream>

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
    /*std::stringstream remainder;

    // align the time difference to 6 (six) digits = milliseconds precision (3 digits) + microseconds precision (3 digits)
    //   because milli-, micro- and nanoseconds have each 3 digits precision
    //   thus when the precision is set to microseconds, the number of tail time digits is cumulative
    //  and pad missing digits with '0' (zeros)
    remainder << std::setw(6) << std::setfill('0') << tailTime.count();
    timestamp << remainder.str();
    return timestamp.str();
    */

    auto secondsSinceEpochInMicroseconds = secondsSinceEpoch * 1'000'000;
#ifdef _DEBUG
    std::cout << secondsSinceEpochInMicroseconds.count() << std::endl;
#endif

    auto currentTimeMicrosecondsRemainder = microsecondsSinceEpoch.count() - secondsSinceEpochInMicroseconds.count();

    // ↓↓ for testing and debug purposes
    // currentTimeMicrosecondsRemainder = 0;
    // currentTimeMicrosecondsRemainder = 1; // for testing and debug purposes
    // currentTimeMicrosecondsRemainder = 12; // for testing and debug purposes
    // currentTimeMicrosecondsRemainder = 123; // for testing and debug purposes
    // currentTimeMicrosecondsRemainder = 1234; // for testing and debug purposes
    // currentTimeMicrosecondsRemainder = 12345; // for testing and debug purposes
    // ^^ for testing and debug purposes

#ifdef _DEBUG
    std::cout << currentTimeMicrosecondsRemainder << std::endl;
    std::cout << timestamp.str() << currentTimeMicrosecondsRemainder << std::endl;
#endif

    std::stringstream suffix;
    suffix
            << std::setw(6) << std::setfill('0')
            << currentTimeMicrosecondsRemainder;
    timestamp << suffix.str();

#ifdef _DEBUG
    assert(6 == suffix.str().length()); // code like yoda
    // timestamp << std::setw(6) << std::setfill('0') << "123"; // for testing and debug purposes
    std::cout << timestamp.str() << std::endl;
    assert(20 == timestamp.str().length()); // code like yoda
#endif

    return timestamp.str();
}
