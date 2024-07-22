//
// Created by laptop on 6/14/24.
//

#include "Timestamp.h"

#include <chrono>
#include <iomanip>

#ifdef _DEBUG
#include <cassert>
#include <iostream>
#endif

std::mutex Timestamp::idGeneratorMutex;

/// @brief Generates timestamp
/// @return timestamp with given precision
std::string Timestamp::generate(Options const & options) {
    std::lock_guard<std::mutex> lock(Timestamp::idGeneratorMutex);

    auto currentTime = std::chrono::system_clock::now();
    auto currentCalendarTime = std::chrono::system_clock::to_time_t(currentTime);
    auto currentLocalCalendarTime = std::localtime(&currentCalendarTime);
    std::stringstream timestamp;

    if (Options::Precision::YEARS == options.getPrecision() ) {
        timestamp << std::put_time(currentLocalCalendarTime, "%Y");
        return timestamp.str();
    }

    if (Options::Precision::MONTHS == options.getPrecision() ) {
        timestamp << std::put_time(currentLocalCalendarTime, "%Y%m");
        return timestamp.str();
    }

    if (Options::Precision::DAYS == options.getPrecision() ) {
        timestamp << std::put_time(currentLocalCalendarTime, "%Y%m%d");
        return timestamp.str();
    }

    if (Options::Precision::HOURS == options.getPrecision() ) {
        timestamp << std::put_time(currentLocalCalendarTime, "%Y%m%d%H");
        return timestamp.str();
    }

    if (Options::Precision::MINUTES == options.getPrecision() ) {
        timestamp << std::put_time(currentLocalCalendarTime, "%Y%m%d%H%M");
        return timestamp.str();
    }

    if (Options::Precision::SECONDS == options.getPrecision() ) {
        timestamp << std::put_time(currentLocalCalendarTime, "%Y%m%d%H%M%S");
        return timestamp.str();
    }

    timestamp << std::put_time(currentLocalCalendarTime, "%Y%m%d%H%M%S");

#ifdef _DEBUG
    std::cout << "timestamp: " << timestamp.str() << std::endl;
#endif

    auto timeSinceEpoch = currentTime.time_since_epoch();
#ifdef _DEBUG
    assert(timeSinceEpoch.count() == currentTime.time_since_epoch().count());
#endif

    auto secondsSinceEpochForSwitch = std::chrono::duration_cast<std::chrono::seconds>(timeSinceEpoch);

#ifdef _DEBUG
    std::cout << "options.getPrecision(): ";
    switch (options.getPrecision()) {
        case Options::Precision::YEARS:
            std::cout << "YEARS" << std::endl;
            break;
        case Options::Precision::MONTHS:
            std::cout << "MONTHS" << std::endl;
            break;
        case Options::Precision::DAYS:
            std::cout << "DAYS" << std::endl;
            break;
        case Options::Precision::HOURS:
            std::cout << "HOURS" << std::endl;
            break;
        case Options::Precision::MINUTES:
            std::cout << "MINUTES" << std::endl;
            break;
        case Options::Precision::SECONDS:
            std::cout << "SECONDS" << std::endl;
            break;
        case Options::Precision::MILLISECONDS:
            std::cout << "MILLISECONDS" << std::endl;
            break;
        case Options::Precision::MICROSECONDS:
            std::cout << "MICROSECONDS" << std::endl;
            break;
        case Options::Precision::NANOSECONDS:
            std::cout << "NANOSECONDS" << std::endl;
            break;
    }
#endif

    switch (options.getPrecision() ) {
        case Options::Precision::MILLISECONDS: {
            auto durationSinceEpochInMilliseconds = std::chrono::duration_cast<std::chrono::milliseconds >(timeSinceEpoch);
            return assembleTimestamp(timestamp, durationSinceEpochInMilliseconds, secondsSinceEpochForSwitch, options);
        }
        case Options::Precision::MICROSECONDS: {
            auto durationSinceEpochInMicroseconds = std::chrono::duration_cast<std::chrono::microseconds >(timeSinceEpoch);
            return assembleTimestamp(timestamp, durationSinceEpochInMicroseconds, secondsSinceEpochForSwitch, options);
        }
        case Options::Precision::NANOSECONDS: {
            auto durationSinceEpochInNanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(timeSinceEpoch);
            return assembleTimestamp(timestamp, durationSinceEpochInNanoseconds, secondsSinceEpochForSwitch, options);
        }
    }

    auto microsecondsSinceEpoch = std::chrono::duration_cast<std::chrono::microseconds>(timeSinceEpoch);
#ifdef _DEBUG
    std::cout << "microsecondsSinceEpoch: " << microsecondsSinceEpoch.count() << std::endl;
#endif

    auto secondsSinceEpoch = std::chrono::duration_cast<std::chrono::seconds>(timeSinceEpoch);
#ifdef _DEBUG
    std::cout << "secondsSinceEpoch: " << secondsSinceEpoch.count() << std::endl;
#endif

    auto tailTime /*chvostikovy cas*/ = microsecondsSinceEpoch - secondsSinceEpoch;
#ifdef _DEBUG
    std::cout << "tailTime: " << tailTime.count() << std::endl;
#endif

    std::stringstream remainder;

    // Create padding - Test Cases
    //   align the time difference to 6 (six) digits = milliseconds precision (3 digits) + microseconds precision (3 digits)
    //   because milli-, micro- and nanoseconds have each 3 digits precision
    //   thus when the precision is set to microseconds, the number of tail time digits is cumulative
    //  and pad missing digits with '0' (zeros)
    // TODO align according to precision
    //  - milliseconds -> 3 chars width
    //  - microseconds -> 6 chars width
    //  -  nanoseconds -> 9 chars width
#ifdef _DEBUG
    std::cout << "options.getPaddingSize(): " << options.getPaddingSize() << std::endl;
#endif

    if (options.isPaddingEnabled() ) {
        remainder << std::setw(6) << std::setfill('0');
    }
    remainder << tailTime.count();

#ifdef _DEBUG
    std::cout << "DEBUG/DEV VERSION!" << std::endl;

    std::cout << "timestamp + remainder: " << timestamp.str() << ' ' << remainder.str() << std::endl;
    std::cout << "timestamp + remainder: " << timestamp.str() << remainder.str() << std::endl;

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

template <typename Time1, typename Time2>
std::string Timestamp::assembleTimestamp(std::stringstream& timestamp, Time1 timeInGivenPrecision, Time2 timeInLowerOrEqualPrecision, Options const & options) {
    auto tailTime /*chvostikovy cas*/ = timeInGivenPrecision - timeInLowerOrEqualPrecision;
#ifdef _DEBUG
    std::cout << "tailTime: " << tailTime.count() << std::endl;
#endif
    std::stringstream remainder;
#ifdef _DEBUG
    std::cout << "options.isPaddingEnabled(): " << options.isPaddingEnabled() << std::endl;
#endif
#ifdef _DEBUG
    std::cout << "options.getPaddingSize(): " << options.getPaddingSize() << std::endl;
#endif
    if (options.isPaddingEnabled()) {
        remainder << std::setw(options.getPaddingSize() ) << std::setfill('0');
    }
    remainder << tailTime.count();
#ifdef _DEBUG
    std::cout << "remainder.str(): " << remainder.str() << std::endl;
#endif
    timestamp << remainder.str();
#ifdef _DEBUG
    std::cout << "timestamp.str(): " << timestamp.str() << std::endl;
#endif
    return timestamp.str();
}