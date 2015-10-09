#pragma once

#include <chrono>

namespace {

using clock = std::chrono::steady_clock;
using duration = std::chrono::steady_clock::duration;
using time_point = std::chrono::steady_clock::time_point;
}
