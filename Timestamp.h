//
// Created by laptop on 6/14/24.
//

#pragma once

#include <mutex>
#include <string>

class Timestamp {
    public:
        static std::string generate();

    private:
        static std::mutex idGeneratorMutex;
};
