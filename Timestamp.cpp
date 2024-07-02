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

    if (Options::Precision::YEAR == options.getPrecision() ) {
        timestamp << std::put_time(currentLocalCalendarTime, "%Y");
        return timestamp.str();
    }

    if (Options::Precision::MONTH == options.getPrecision() ) {
        timestamp << std::put_time(currentLocalCalendarTime, "%Y%m");
        return timestamp.str();
    }

    if (Options::Precision::DAY == options.getPrecision() ) {
        timestamp << std::put_time(currentLocalCalendarTime, "%Y%m%d");
        return timestamp.str();
    }

    if (Options::Precision::HOUR == options.getPrecision() ) {
        timestamp << std::put_time(currentLocalCalendarTime, "%Y%m%d%H");
        return timestamp.str();
    }

    if (Options::Precision::MINUTE == options.getPrecision() ) {
        timestamp << std::put_time(currentLocalCalendarTime, "%Y%m%d%H%M");
        return timestamp.str();
    }

    if (Options::Precision::SECOND == options.getPrecision() ) {
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

    // TODO change precision by the 'options' parameter
    /*
    if (Options::Precision::MILLISECOND == options.getPrecision() ) {
        durationSinceEpochInGivenPrecision = std::chrono::duration_cast<std::chrono::milliseconds >(timeSinceEpoch);
    }

    if (Options::Precision::MICROSECONDS == options.getPrecision() ) {
        durationSinceEpochInGivenPrecision = std::chrono::duration_cast<std::chrono::milliseconds >(timeSinceEpoch);
    }

    if (Options::Precision::MILLISECOND == options.getPrecision() ) {
        durationSinceEpochInGivenPrecision = std::chrono::duration_cast<std::chrono::milliseconds >(timeSinceEpoch);
    }*/

    auto durationSinceEpochInGivenPrecision = std::chrono::duration_cast<std::chrono::nanoseconds>(timeSinceEpoch);

    auto durationSinceEpochInMilliseconds = std::chrono::duration_cast<std::chrono::milliseconds >(timeSinceEpoch);
    auto durationSinceEpochInMicroseconds = std::chrono::duration_cast<std::chrono::microseconds >(timeSinceEpoch);
    auto durationSinceEpochInNanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(timeSinceEpoch);

    auto secondsSinceEpochForSwitch = std::chrono::duration_cast<std::chrono::seconds>(timeSinceEpoch);

#ifdef _DEBUG
    std::cout << "options.getPrecision(): " << options.getPrecision() << std::endl;
#endif

    switch (options.getPrecision() ) {
        case Options::MILLISECOND: {
            durationSinceEpochInGivenPrecision = std::chrono::duration_cast<std::chrono::milliseconds>(timeSinceEpoch);
            auto tailTime /*chvostikovy cas*/ = durationSinceEpochInMilliseconds - secondsSinceEpochForSwitch;
            std::stringstream remainder;
            if (options.isPaddingEnabled()) {
                remainder << std::setw(3) << std::setfill('0');
            }
            remainder << tailTime.count();
            timestamp << remainder.str();
            return timestamp.str();
//            break;
        }
        case Options::MICROSECONDS: {
            durationSinceEpochInGivenPrecision = std::chrono::duration_cast<std::chrono::microseconds >(timeSinceEpoch);
            auto tailTime /*chvostikovy cas*/ = durationSinceEpochInMicroseconds - secondsSinceEpochForSwitch;
            std::stringstream remainder;
            if (options.isPaddingEnabled() ) {
                remainder << std::setw(6) << std::setfill('0');
            }
            remainder << tailTime.count();
            timestamp << remainder.str();
            return timestamp.str();
//            break;
        }
        case Options::NANOSECONDS: {
            durationSinceEpochInGivenPrecision = std::chrono::duration_cast<std::chrono::nanoseconds >(timeSinceEpoch);
            auto tailTime /*chvostikovy cas*/ = durationSinceEpochInNanoseconds - secondsSinceEpochForSwitch;
            std::stringstream remainder;
            if (options.isPaddingEnabled()) {
                remainder << std::setw(9) << std::setfill('0');
            }
            remainder << tailTime.count();
            timestamp << remainder.str();
            return timestamp.str();
//            break;
        }
//        default:
//            durationSinceEpochInGivenPrecision = std::chrono::duration_cast<std::chrono::microseconds>(timeSinceEpoch);
    }

#ifdef _DEBUG
    std::cout << "durationSinceEpochInGivenPrecision: " << durationSinceEpochInGivenPrecision.count() << std::endl;
#endif

    auto microsecondsSinceEpoch = std::chrono::duration_cast<std::chrono::microseconds>(timeSinceEpoch);
#ifdef _DEBUG
    std::cout << "microsecondsSinceEpoch: " << microsecondsSinceEpoch.count() << std::endl;
#endif

    auto secondsSinceEpoch = std::chrono::duration_cast<std::chrono::seconds>(timeSinceEpoch);
#ifdef _DEBUG
    std::cout << "secondsSinceEpoch: " << secondsSinceEpoch.count() << std::endl;
#endif

    auto tailTime /*chvostikovy cas*/ = microsecondsSinceEpoch - secondsSinceEpoch;
//    auto tailTime /*chvostikovy cas*/ = durationSinceEpochInGivenPrecision - secondsSinceEpoch;
#ifdef _DEBUG
    std::cout << "tailTime: " << tailTime.count() << std::endl;
#endif

    std::stringstream remainder;

    // Create padding
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
