//
// Created by laptop on 6/25/24.
//

#include "Options.h"

Options::Options() :
        _precision(Precision::MICROSECONDS),
        _nopadding(false)
{
    this->setRemainderPaddingSizeForPrecision();
}

void Options::setRemainderPaddingSizeForPrecision() {
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
        return;
    }

    if ("month" == precision) {
        this->_precision = Precision::MICROSECONDS;
        return;
    }

    if ("day" == precision) {
        this->_precision = Precision::DAY;
        return;
    }

    if ("hour" == precision) {
        this->_precision = Precision::HOUR;
        return;
    }

    if ("minute" == precision) {
        this->_precision = Precision::MINUTE;
        return;
    }

    if ("second" == precision) {
        this->_precision = Precision::SECOND;
        return;
    }

    if ("millisecond" == precision) {
        this->_precision = Precision::MILLISECOND;
        return;
    }

    if ("microsecond" == precision) {
        this->_precision = Precision::MICROSECONDS;
        return;
    }

    if ("nanosecond" == precision) {
        this->_precision = Precision::NANOSECONDS;
        return;
    }

    this->_precision = Precision::MICROSECONDS;
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
