#include <cstdint>
#include <cstddef>

enum class EventType {
    TOUCH_PRESS,
    TOUCH_RELEASE,
    BUTTON_PRESS,
    TIMER_TICK,
    POWER_LOW,
    APP_EXIT
};

struct Event {
    EventType type;
    void* data;
    uint32_t timestamp;
};

class AEventListener {
public:
    virtual ~AEventListener() = default;
    virtual void onEvent(const Event& event) = 0;
};

class EventService {
private:
    static const size_t MAX_LISTENERS = 10;
    AEventListener* listeners_[MAX_LISTENERS];
    size_t listenerCount_;
    
    Event eventQueue_[32];
    size_t queueHead_;
    size_t queueTail_;
    
public:
    EventService();
    
    void addListener(AEventListener* listener);
    void removeListener(AEventListener* listener);
    void postEvent(const Event& event);
    void processEvents();
};
