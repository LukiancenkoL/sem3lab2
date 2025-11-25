#ifndef TIMER_H
#define TIMER_H

#include <chrono>
#include <QElapsedTimer>
#include <qobject.h>
#include <qtypes.h>
#include <QString>

class Timer
{
public:
    Timer(const std::chrono::milliseconds &total);
    Timer(const std::chrono::milliseconds &total, const QString &documentPath);

    bool paused() const;
    std::chrono::milliseconds total() const;
    std::chrono::milliseconds remaining() const;
    void setRemaining(const std::chrono::milliseconds &remaining);
    const QElapsedTimer &elapsed() const;
    const QString &documentPath() const;
    void elapsedStart();
    quint64 elapsedRestart();
    void pause();
    void resume();

private:
    std::chrono::milliseconds m_total{};
    std::chrono::milliseconds m_remaining{};
    bool m_paused = false;
    QElapsedTimer m_elapsed{};
    QString m_documentPath{};
};

#endif // !TIMER_H
