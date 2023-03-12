#include "clock.h"

using namespace cv;

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
    return averageDuration;
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
