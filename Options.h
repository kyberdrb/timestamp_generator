//
// Created by laptop on 6/25/24.
//

#pragma once

#include <string>

class Options {
public:
    Options();

    enum Precision {
        YEAR,
        MONTH,
        DAY,
        HOUR,
        MINUTE,
        SECOND,
        MILLISECOND,
        MICROSECONDS,
        NANOSECONDS
    };

    void setPrecision(std::string precision);
    void disablePadding();

    Precision getPrecision() const;
    bool isPaddingEnabled() const;

private:
    Precision _precision;
    bool _nopadding;
};
