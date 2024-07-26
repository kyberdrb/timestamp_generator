//
// Created by laptop on 6/14/24.
//

#include "Timestamp.h"

#include "Options.h"

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

#ifdef _DEBUG
    std::cout << "options.getPrecision(): ";
#endif
    switch (options.getPrecision()) {
        case Options::Precision::YEARS:
#ifdef _DEBUG
            std::cout << "YEARS" << std::endl;
#endif
            timestamp << std::put_time(currentLocalCalendarTime, "%Y");
            return timestamp.str();
        case Options::Precision::MONTHS:
#ifdef _DEBUG
            std::cout << "MONTHS" << std::endl;
#endif
            timestamp << std::put_time(currentLocalCalendarTime, "%Y%m");
            return timestamp.str();
        case Options::Precision::DAYS:
#ifdef _DEBUG
            std::cout << "DAYS" << std::endl;
#endif
            timestamp << std::put_time(currentLocalCalendarTime, "%Y%m%d");
            return timestamp.str();
        case Options::Precision::HOURS:
#ifdef _DEBUG
            std::cout << "HOURS" << std::endl;
#endif
            timestamp << std::put_time(currentLocalCalendarTime, "%Y%m%d%H");
            return timestamp.str();
        case Options::Precision::MINUTES:
#ifdef _DEBUG
            std::cout << "MINUTES" << std::endl;
#endif
            timestamp << std::put_time(currentLocalCalendarTime, "%Y%m%d%H%M");
            return timestamp.str();
        case Options::Precision::SECONDS:
#ifdef _DEBUG
            std::cout << "SECONDS" << std::endl;
#endif
            timestamp << std::put_time(currentLocalCalendarTime, "%Y%m%d%H%M%S");
            return timestamp.str();
        case Options::Precision::MILLISECONDS: {
#ifdef _DEBUG
            std::cout << "MILLISECONDS" << std::endl;
#endif
// TODO START encapsulate to separate function
            timestamp << std::put_time(currentLocalCalendarTime, "%Y%m%d%H%M%S");

#ifdef _DEBUG
            std::cout << "timestamp: " << timestamp.str() << std::endl;
#endif

            auto timeSinceEpoch = currentTime.time_since_epoch();
#ifdef _DEBUG
            assert(timeSinceEpoch.count() == currentTime.time_since_epoch().count());
#endif

            auto secondsSinceEpochForSwitch = std::chrono::duration_cast<std::chrono::seconds>(timeSinceEpoch);
// TODO END encapsulate to separate function

            auto durationSinceEpochInMilliseconds = std::chrono::duration_cast<std::chrono::milliseconds >(timeSinceEpoch);
            return assembleTimestamp(timestamp, durationSinceEpochInMilliseconds, secondsSinceEpochForSwitch, options);
        }
        case Options::Precision::MICROSECONDS: {
#ifdef _DEBUG
            std::cout << "MICROSECONDS" << std::endl;
#endif
            timestamp << std::put_time(currentLocalCalendarTime, "%Y%m%d%H%M%S");

#ifdef _DEBUG
            std::cout << "timestamp: " << timestamp.str() << std::endl;
#endif

            auto timeSinceEpoch = currentTime.time_since_epoch();
#ifdef _DEBUG
            assert(timeSinceEpoch.count() == currentTime.time_since_epoch().count());
#endif

            auto secondsSinceEpochForSwitch = std::chrono::duration_cast<std::chrono::seconds>(timeSinceEpoch);

            auto durationSinceEpochInMicroseconds = std::chrono::duration_cast<std::chrono::microseconds >(timeSinceEpoch);
            return assembleTimestamp(timestamp, durationSinceEpochInMicroseconds, secondsSinceEpochForSwitch, options);
        }
        case Options::Precision::NANOSECONDS: {
#ifdef _DEBUG
            std::cout << "NANOSECONDS" << std::endl;
#endif
            timestamp << std::put_time(currentLocalCalendarTime, "%Y%m%d%H%M%S");

#ifdef _DEBUG
            std::cout << "timestamp: " << timestamp.str() << std::endl;
#endif

            auto timeSinceEpoch = currentTime.time_since_epoch();
#ifdef _DEBUG
            assert(timeSinceEpoch.count() == currentTime.time_since_epoch().count());
#endif

            auto secondsSinceEpochForSwitch = std::chrono::duration_cast<std::chrono::seconds>(timeSinceEpoch);

            auto durationSinceEpochInNanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(timeSinceEpoch);
            return assembleTimestamp(timestamp, durationSinceEpochInNanoseconds, secondsSinceEpochForSwitch, options);
        }
        default:
#ifdef _DEBUG
            std::cout << "Unknown precision" << std::endl;
#endif
            timestamp << std::put_time(currentLocalCalendarTime, "%Y%m%d%H%M%S");
    }

    return timestamp.str();
}

template <typename Time1, typename Time2>
std::string Timestamp::assembleTimestamp(std::stringstream& timestamp, Time1 timeInGivenPrecision, Time2 timeInLowerOrEqualPrecision, Options const & options) {
    auto tailTime /*chvostikovy cas*/ = timeInGivenPrecision - timeInLowerOrEqualPrecision;

#ifdef _DEBUG
    std::cout << "tailTime: " << tailTime.count() << std::endl;
#endif
#ifdef _DEBUG
    std::cout << "options.isPaddingEnabled(): " << options.isPaddingEnabled() << std::endl;
#endif
#ifdef _DEBUG
    std::cout << "options.getPaddingSize(): " << options.getPaddingSize() << std::endl;
#endif

    std::stringstream remainder;
    if (options.isPaddingEnabled()) {
        remainder << std::setw(options.getPaddingSize() ) << std::setfill('0');
    }
    remainder << tailTime.count();

#ifdef _DEBUG
    std::cout << "timestamp.str(): " << timestamp.str() << std::endl;
    std::cout << "timestamp.str().size(): " << timestamp.str().size() << std::endl;
#endif
#ifdef _DEBUG
    std::cout << "remainder.str(): " << remainder.str() << std::endl;
    std::cout << "remainder.str().size(): " << remainder.str().size() << std::endl;
#endif

    timestamp << remainder.str();

#ifdef _DEBUG
    std::cout << "timestamp.str(): " << timestamp.str() << std::endl;
    std::cout << "timestamp.str().size(): " << timestamp.str().size() << std::endl;
#endif
    return timestamp.str();
}
