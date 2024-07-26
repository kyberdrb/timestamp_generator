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
