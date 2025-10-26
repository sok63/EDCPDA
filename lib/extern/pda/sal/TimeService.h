#include <cstdint>
#include <cstddef>

class TimerService {
public:
    using TimerCallback = void(*)(void* userData);
    
private:
    struct Timer {
        uint32_t interval;
        uint32_t lastTrigger;
        bool repeat;
        bool active;
        TimerCallback callback;
        void* userData;
    };
    
    static const size_t MAX_TIMERS = 16;
    Timer timers_[MAX_TIMERS];
    
public:
    TimerService();
    
    int createTimer(uint32_t interval, bool repeat, TimerCallback callback, void* userData);
    void startTimer(int timerId);
    void stopTimer(int timerId);
    void deleteTimer(int timerId);
    void update();
};