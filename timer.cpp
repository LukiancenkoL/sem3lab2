#include "timer.h"
#include <chrono>
#include <qtypes.h>

Timer::Timer(const std::chrono::milliseconds &total) : m_total(total), m_remaining(total) { };

Timer::Timer(const std::chrono::milliseconds &total, const QString &documentPath)
    : m_total(total), m_remaining(total), m_documentPath{ documentPath } { };

bool Timer::paused() const
{
    return this->m_paused;
}

std::chrono::milliseconds Timer::total() const
{
    return this->m_total;
}

std::chrono::milliseconds Timer::remaining() const
{
    return this->m_remaining;
}
void Timer::setRemaining(const std::chrono::milliseconds &remaining)
{
    this->m_remaining = remaining;
}
const QElapsedTimer &Timer::elapsed() const
{
    return this->m_elapsed;
}
const QString &Timer::documentPath() const
{
    return this->m_documentPath;
}
quint64 Timer::elapsedRestart()
{
    return this->m_elapsed.restart();
}
void Timer::elapsedStart()
{
    return this->m_elapsed.start();
}
void Timer::pause()
{
    this->m_paused = true;
}
void Timer::resume()
{
    this->m_paused = false;
    this->m_elapsed.restart();
}
