#include "clock.h"

using namespace cv::engine;

Clock::Clock()
    : m_durations()
{}

Clock::~Clock() {}

Clock::DurationT
Clock::GetTimeDelta()
{
    DurationT averageDuration;
    for (const auto& duration : m_durations) {
        averageDuration += duration;
    }
    averageDuration /= k_durationCount;
    return averageDuration < std::chrono::seconds(1)
               ? averageDuration
               : std::chrono::milliseconds(30);
}

void
Clock::Start()
{
    m_currentTime = m_clock.now();
    m_currentDuration += 1;
    m_currentDuration %= k_durationCount;
}

void
Clock::Stop()
{
    m_durations[m_currentDuration] = m_clock.now() - m_currentTime;
}
