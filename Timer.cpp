//
// Created by iria on 11.11.2019.
//

#include <iostream>
#include "Timer.h"

Timer::Timer() {
    this->start = std::chrono::high_resolution_clock::now();
}

void Timer::log_time(const std::string& msg) {
    auto current_time = std::chrono::high_resolution_clock::now();
    auto diff = (current_time - this->start).count();
    printf("[%4ld.%-6ld] %s\n", diff/1000000000, diff%1000000000, msg.c_str());
}

