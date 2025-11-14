#pragma once

#include <cstddef>
#include <cstdint>

using TimerCallback = void (*)(void* userData);

struct Timer
{
    uint32_t interval;
    uint32_t lastTrigger;
    bool repeat;
    bool active;
    TimerCallback callback;
    void* userData;
};

class TimerService
{
public:
    TimerService();

    int createTimer(uint32_t interval, bool repeat, TimerCallback callback, void* userData);
    void startTimer(int timerId);
    void stopTimer(int timerId);
    void deleteTimer(int timerId);
    void update();

private:
    static const size_t MAX_TIMERS = 16;
    Timer timers_[MAX_TIMERS];
};