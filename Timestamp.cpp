//
// Created by laptop on 6/14/24.
//

#include "Timestamp.h"

#include "Options.h"

#include <chrono>
#include <iomanip>
#include <iostream>

#ifdef _DEBUG
#include <cassert>
    #ifdef _MSC_VER
        #include <iostream>
    #endif
#endif

std::mutex Timestamp::timestampGeneratorMutex;

// Explicit template instantiation
template std::chrono::system_clock::duration Timestamp::extractTimeSinceEpoch<std::chrono::system_clock::time_point>(std::stringstream& timestamp, tm*& currentLocalCalendarTime, const std::chrono::system_clock::time_point& currentTime);

template std::string Timestamp::handlePrecision<std::chrono::milliseconds>(std::stringstream&, tm*&, const std::chrono::system_clock::time_point&, const Options&);
template std::string Timestamp::handlePrecision<std::chrono::microseconds>(std::stringstream&, tm*&, const std::chrono::system_clock::time_point&, const Options&);
template std::string Timestamp::handlePrecision<std::chrono::nanoseconds>(std::stringstream&, tm*&, const std::chrono::system_clock::time_point&, const Options&);

/// @brief Generates timestamp
/// @return timestamp with given precision
std::string Timestamp::generate(Options const & options) {
    std::lock_guard<std::mutex> lock(Timestamp::timestampGeneratorMutex);

    auto currentTime = std::chrono::system_clock::now();
    auto currentCalendarTime = std::chrono::system_clock::to_time_t(currentTime);

    if (currentCalendarTime == -1) {
        std::cerr << "Failed to get the current calendar time" << std::endl;
        return std::string{};
    }

    struct tm currentLocalCalendarTimeRaw{};
    tm* currentLocalCalendarTime = &currentLocalCalendarTimeRaw;

#ifndef _MSC_VER
    #ifdef _DEBUG
        std::cout << "Using thread-safe 'localtime_r' function for POSIX systems" << std::endl;
    #endif
    localtime_r(&currentCalendarTime, currentLocalCalendarTime);
#else
    #ifdef _DEBUG
        std::cout << "Using thread-safe 'localtime_s' function for Windows systems with MSVC compiler" << std::endl;
    #endif
    {
        errno_t err = localtime_s(currentLocalCalendarTime, &currentCalendarTime);
        if (err) {
            std::cerr << "Failed to convert calendar time to local time" << std::endl;
            return std::string{};
        }
    }
#endif

#ifndef _MSC_VER
    #ifdef _DEBUG
        std::cout << "Current local time (using POSIX compatible function 'std::asctime'): " << std::asctime(currentLocalCalendarTime);
    #endif
#else
    #ifdef _DEBUG
        std::cout << "Current local time (using 'std::asctime_s' to resolve warning at building with MSVC compiler for thread safety and buffer size safety): " << std::asctime(currentLocalCalendarTime);
    #endif

    char buffer[100];
    {
        errno_t err = asctime_s(buffer, sizeof(buffer), currentLocalCalendarTime);
        if (err != 0) {
            std::cerr << "Error converting time" << std::endl;
        } else {
            std::cout << "Current local time: " << buffer;
        }
    }
#endif

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

            // TODO add option '-f'/'--format' to change the base timestamp: will work alone or with combination with the option  'precision' with values 'milli/micro/nanoseconds' to add high precision remainder values
//            timestamp << std::put_time(currentLocalCalendarTime, options->getTimeFormatString());
            return timestamp.str();
        case Options::Precision::MILLISECONDS:
#ifdef _DEBUG
            std::cout << "MILLISECONDS" << std::endl;
#endif
            return handlePrecision<std::chrono::milliseconds>(timestamp, currentLocalCalendarTime, currentTime, options);

        case Options::Precision::MICROSECONDS:
#ifdef _DEBUG
            std::cout << "MICROSECONDS" << std::endl;
#endif
            return handlePrecision<std::chrono::microseconds>(timestamp, currentLocalCalendarTime, currentTime, options);

        case Options::Precision::NANOSECONDS:
#ifdef _DEBUG
            std::cout << "NANOSECONDS" << std::endl;
#endif
            return handlePrecision<std::chrono::nanoseconds>(timestamp, currentLocalCalendarTime, currentTime, options);

        default:
#ifdef _DEBUG
            std::cout << "Unknown precision" << std::endl;
#endif
            timestamp << std::put_time(currentLocalCalendarTime, "%Y%m%d%H%M%S");
    }

    return timestamp.str();
}

template <typename Duration>
std::string Timestamp::handlePrecision(std::stringstream& timestamp, tm*& currentLocalCalendarTime, const std::chrono::system_clock::time_point& currentTime, const Options& options) {
    auto timeSinceEpoch = extractTimeSinceEpoch(timestamp, currentLocalCalendarTime, currentTime);
    auto secondsSinceEpochForSwitch = std::chrono::duration_cast<std::chrono::seconds>(timeSinceEpoch);
    auto durationSinceEpoch = std::chrono::duration_cast<Duration>(timeSinceEpoch);
    return assembleTimestamp(timestamp, durationSinceEpoch, secondsSinceEpochForSwitch, options);
}

template <typename TimePoint>
auto Timestamp::extractTimeSinceEpoch(std::stringstream& timestamp, tm*& currentLocalCalendarTime, const TimePoint& currentTime) -> decltype(currentTime.time_since_epoch()) {
    auto timeSinceEpoch = currentTime.time_since_epoch();
    timestamp << std::put_time(currentLocalCalendarTime, "%Y%m%d%H%M%S");

#ifdef _DEBUG
    std::cout << "timestamp: " << timestamp.str() << std::endl;
#endif
#ifdef _DEBUG
    assert(timeSinceEpoch.count() == currentTime.time_since_epoch().count());
#endif

    return timeSinceEpoch;
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
