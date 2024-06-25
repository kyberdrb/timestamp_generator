//
// Created by laptop on 6/14/24.
//

#pragma once

#include "Options.h"

#include <mutex>
#include <string>

class Timestamp {
    public:
        static std::string generate(Options const & options);

    private:
        static std::mutex idGeneratorMutex;
};
