//
// Created by laptop on 6/25/24.
//

#include "Options.h"

Options::Options() :
    _precision(Precision::NANOSECONDS),
    _nopadding(false)
{}

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
