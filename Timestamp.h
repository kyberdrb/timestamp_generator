//
// Created by laptop on 6/14/24.
//

#pragma once

#include <chrono>
#include <mutex>
#include <string>

class Options;

class Timestamp {
    public:
        static std::string generate(Options const & options);

    private:
        static std::mutex timestampGeneratorMutex;

        template <typename TimePoint>
        static auto extractTimeSinceEpoch(std::stringstream& timestamp, tm*& currentLocalCalendarTime, const TimePoint& currentTime) -> decltype(currentTime.time_since_epoch());

        template <typename Time1, typename Time2>
        static std::string assembleTimestamp(std::stringstream& timestamp, Time1 timeInGivenPrecision, Time2 timeInLowerOrEqualPrecision, Options const & options);
};
