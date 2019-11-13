//
// Created by iria on 11.11.2019.
//
#pragma once

#include <chrono>
#include <string>

class Timer {
private:
    std::chrono::system_clock::time_point start;
public:
    Timer();
    void log_time(const std::string& msg);
};


