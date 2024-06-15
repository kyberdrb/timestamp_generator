//
// Created by laptop on 6/14/24.
//

#pragma once

#include <mutex>
#include <string>

class IDGenerator {
    public:
        static std::string generateTimestamp();

    private:
        static std::mutex idGeneratorMutex;
};
