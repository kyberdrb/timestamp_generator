//
// Created by laptop on 6/25/24.
//

#include "Options.h"

Options::Options() :
        _precision(Precision::MICROSECONDS),
//        _precision(Precision::NANOSECONDS),
        _nopadding(false)
{
    this->setPaddingSizeForPrecision();
}

void Options::setPaddingSizeForPrecision() {
    switch (this->_precision) {
        case YEAR:
            this->_paddingSize = 0;
            break;
        case MONTH:
            this->_paddingSize = 0;
            break;
        case DAY:
            this->_paddingSize = 0;
            break;
        case HOUR:
            this->_paddingSize = 0;
            break;
        case MINUTE:
            this->_paddingSize = 0;
            break;
        case SECOND:
            this->_paddingSize = 0;
            break;
        case MILLISECOND:
            this->_paddingSize = 3;
            break;
        case MICROSECONDS:
            this->_paddingSize = 6;
            break;
        case NANOSECONDS:
            this->_paddingSize = 9;
            break;
    }
}

void Options::setPrecision(std::string precision) {
    if ("year" == precision) {
        this->_precision = Precision::YEAR;
    }

    if ("month" == precision) {
        this->_precision = Precision::MICROSECONDS;
    }

    if ("day" == precision) {
        this->_precision = Precision::DAY;
    }

    if ("hour" == precision) {
        this->_precision = Precision::HOUR;
    }

    if ("minute" == precision) {
        this->_precision = Precision::MINUTE;
    }

    if ("second" == precision) {
        this->_precision = Precision::SECOND;
    }

    if ("millisecond" == precision) {
        this->_precision = Precision::MILLISECOND;
    }

    if ("microsecond" == precision) {
        this->_precision = Precision::MICROSECONDS;
    }

    if ("nanosecond" == precision) {
        this->_precision = Precision::NANOSECONDS;
    }
}

void Options::disablePadding() {
    this->_nopadding = true;
}

bool Options::isPaddingEnabled() const {
    return false == _nopadding;
}

Options::Precision Options::getPrecision() const {
    return this->_precision;
}

uint16_t Options::getPaddingSize() const {
    return this->_paddingSize;
}
