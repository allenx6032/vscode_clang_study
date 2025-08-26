/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-theo.liennard
** File description:
** Game Engine
*/

#pragma once
#include <chrono>
#include <functional>
#include <iostream>
#include <map>
#include <thread>

class TimeManager {
    public:
        TimeManager();
        ~TimeManager();

    public:
        /**
         * @brief Execute a function after a timeout
         *
         * @param f A function to execute after the timeout
         * @param timeout The timeout in milliseconds
         */
        void timeSetTimeout(std::function<void()> f, time_t timeout);

        /**
         * @brief Execute a function every tickTime
         *
         * @param f A function to execute every tickTime
         * @param tickTime The tickTime in milliseconds
         *
         * @return A function to remove the function from the tick execution
         */
        std::function<void()> timeSetInterval(std::function<void()> f, time_t tickTime);

        /**
         * @brief Stop the tick
         */
        void timeStopTick();

        /**
         * @brief Start the tick
         */
        void timeStartTick();

    private:
        /**
         * @brief Update the tick
         */
        void timeUpdateTick();

    private:
        bool _stop = false;

        // map of tickTime and functions to execute so we have different tick times for different functions
        std::map<time_t, std::vector<std::function<void()>>> _tickFunctionsMap;
};
