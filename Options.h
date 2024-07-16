//
// Created by laptop on 6/25/24.
//

#pragma once

#include <cstdint>
#include <string>

class Options {
public:
    Options();

    enum Precision {
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

    void setPrecision(std::string precision);
    void disablePadding();

    Precision getPrecision() const;
    bool isPaddingEnabled() const;
    uint16_t getPaddingSize() const;

private:
    Precision _precision;
    bool _nopadding;
    uint16_t _paddingSize;

    void setRemainderPaddingSizeForPrecision();
};
