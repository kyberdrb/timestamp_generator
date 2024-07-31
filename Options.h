//
// Created by laptop on 6/25/24.
//

#pragma once

#include <cstdint>
#include <string>

class Options {
public:
    Options();

    enum class Precision {
        YEARS,
        MONTHS,
        DAYS,
        HOURS,
        MINUTES,
        SECONDS,
        MILLISECONDS,
        MICROSECONDS,
        NANOSECONDS
    };

    void setPrecision(std::string character);
    void disablePadding();

    Precision getPrecision() const;
    bool isPaddingEnabled() const;
    uint16_t getPaddingSize() const;

    // TODO add option '-f'/'--format' to change the base timestamp: will work alone or with combination with the option  'precision' with values 'milli/micro/nanoseconds' to add high precision remainder values
//    std::string getTimeFormatString() const;

private:
    Precision _precision;
    bool _nopadding;
    uint16_t _paddingSize;

    void setRemainderPaddingSizeForPrecision();
};
