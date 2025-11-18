#ifndef TIMER_H
#define TIMER_H

#include <chrono>
#include <QElapsedTimer>

class Timer
{
public:
    Timer(std::chrono::milliseconds total)
        : total(total)
        , remaining(total) {};
    std::chrono::milliseconds total{};
    std::chrono::milliseconds remaining{};
    bool paused = false;
    QElapsedTimer elaplsed{};
};

#endif // !TIMER_H
