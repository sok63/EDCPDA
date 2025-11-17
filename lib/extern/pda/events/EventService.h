#pragma once

#include <cstddef>
#include <cstdint>

enum class eEventType
{
    UNKNOWN_TYPE,
    TOUCH_EVENT,
    BUTTON_EVENT,
    KEY_CHAR_EVENT,
    TIMER_EVENT,
    POWER_EVENT,
    APPLICATION_EVENT
};

struct Event
{
    eEventType type = eEventType::UNKNOWN_TYPE;
    uint8_t data[32];
    uint32_t timestamp;
};

class AEventListener
{
public:
    virtual ~AEventListener() = default;
    virtual bool onEvent(const Event& event) = 0;
};

class EventService
{
public:
    EventService();

    void addListener(AEventListener* listener);
    void removeListener(AEventListener* listener);
    void postEvent(const Event& event);

private:
    static const size_t MAX_LISTENERS = 10;
    AEventListener* listeners_[MAX_LISTENERS];
};
