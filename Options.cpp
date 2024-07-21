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
        case Precision::YEARS:
            this->_paddingSize = 0;
            break;
        case Precision::MONTHS:
            this->_paddingSize = 0;
            break;
        case Precision::DAYS:
            this->_paddingSize = 0;
            break;
        case Precision::HOURS:
            this->_paddingSize = 0;
            break;
        case Precision::MINUTES:
            this->_paddingSize = 0;
            break;
        case Precision::SECONDS:
            this->_paddingSize = 0;
            break;
        case Precision::MILLISECONDS:
            this->_paddingSize = 3;
            break;
        case Precision::MICROSECONDS:
            this->_paddingSize = 6;
            break;
        case Precision::NANOSECONDS:
            this->_paddingSize = 9;
            break;
    }
}

void Options::setPrecision(std::string precision) {
    if ("years" == precision) {
        this->_precision = Precision::YEARS;
    }

    if ("months" == precision) {
        this->_precision = Precision::MONTHS;
    }

    if ("days" == precision) {
        this->_precision = Precision::DAYS;
    }

    if ("hours" == precision) {
        this->_precision = Precision::HOURS;
    }

    if ("minutes" == precision) {
        this->_precision = Precision::MINUTES;
    }

    if ("seconds" == precision) {
        this->_precision = Precision::SECONDS;
    }

    if ("milliseconds" == precision) {
        this->_precision = Precision::MILLISECONDS;
    }

    if ("microseconds" == precision) {
        this->_precision = Precision::MICROSECONDS;
    }

    if ("nanoseconds" == precision) {
        this->_precision = Precision::NANOSECONDS;
    }

    this->setRemainderPaddingSizeForPrecision();
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
