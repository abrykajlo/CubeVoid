#pragma once

#include <chrono>
#include <array>

namespace cv {
class Clock
{
  public:
    Clock();
    ~Clock();

    using ClockT = std::chrono::high_resolution_clock;
    using TimeT = std::chrono::time_point<ClockT>;
    using DurationT = std::chrono::nanoseconds;
    
    DurationT GetTimeDelta();
    void Start();
    void Stop();

  private:
    static constexpr int k_durationCount = 5;

    ClockT m_clock;
    TimeT m_currentTime;
    std::array<DurationT, k_durationCount> m_durations;
    int m_currentDuration = 0;
};
}