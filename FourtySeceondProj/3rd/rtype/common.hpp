#pragma once

//all
#include <asio/asio.hpp>

#include <iostream>
#include <vector>
#include <cstring>
#include <cstdint>
#include <chrono>
#include <thread>
#include <set>

//queue
#include <mutex>
#include <deque>
#include <condition_variable>

enum class owner {
    Server,
    Client,
    None
};
