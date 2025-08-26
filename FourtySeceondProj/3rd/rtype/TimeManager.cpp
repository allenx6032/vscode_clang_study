/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-theo.liennard
** File description:
** Game Engine
*/

#include "TimeManager.hpp"

TimeManager::TimeManager() {};

TimeManager::~TimeManager() {
    _stop = true;
};

void TimeManager::timeSetTimeout(std::function<void()> f, time_t timeout) {
    std::thread([f, timeout](){
        std::this_thread::sleep_for(std::chrono::milliseconds(timeout));
        f();
    }).detach();
};

std::function<void()> TimeManager::timeSetInterval(std::function<void()> f, time_t tickTime) {
    _tickFunctionsMap[tickTime].push_back(f);

    // iterator to the element we just added so we can remove it later if needed
    auto var = _tickFunctionsMap[tickTime].end() - 1;

    return [this, tickTime, var](){
        _tickFunctionsMap[tickTime].erase(var);
    };
};

void TimeManager::timeStopTick() {
    _stop = true;
};

void TimeManager::timeStartTick() {
    _stop = false;
    timeUpdateTick();
};

void TimeManager::timeUpdateTick() {
    for (auto &tickFunctions : _tickFunctionsMap) {
        std::thread([this, &tickFunctions](){
            while (true) {
                std::this_thread::sleep_for(std::chrono::milliseconds(tickFunctions.first));
                if (_stop)
                    break;
                if (tickFunctions.second.size() == 0)
                    break;
                for (auto &f : tickFunctions.second)
                    f();
            }
        }).detach();
    }
};

