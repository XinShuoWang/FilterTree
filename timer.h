#pragma once

#include <iostream>
#include <chrono>

class Timer {
private:
    std::chrono::time_point<std::chrono::steady_clock> start_;
    std::chrono::time_point<std::chrono::steady_clock> end_;
public:
    Timer()
    {
        start_ = std::chrono::steady_clock::now();
    }
    ~Timer()
    {
        end_ = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsed_seconds = end_ - start_;
        std::cout << "Elapsed time: " << elapsed_seconds.count() << "s\n";
    }
};