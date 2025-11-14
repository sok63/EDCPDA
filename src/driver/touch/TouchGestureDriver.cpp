#include "TouchGestureDriver.h"
#include <cmath>
#include <cstring>

int16_t TouchGestureDriver::TouchPoint::distanceTo(const TouchPoint& other) const
{
    int16_t dx = other.x - x;
    int16_t dy = other.y - y;
    return static_cast<int16_t>(sqrt(dx * dx + dy * dy));
}

TouchGestureDriver::TouchGestureDriver(const sTouchConfig& config)
    : config_(config)
    , state_(eTouchState::IDLE)
    , lastTapTime_(0)
    , lastEventTime_(0)
    , waitingForSecondTap_(false)
    , longPressReported_(false)
    , dragStartReported_(false)
    , queueHead_(0)
    , queueTail_(0)
    , queueCount_(0)
{
    eventQueue_ = new sTouchEvent[config_.eventQueueSize];
}

TouchGestureDriver::~TouchGestureDriver()
{
    delete[] eventQueue_;
}

void TouchGestureDriver::update(const sTouchInput& input)
{
    if (input.justPressed) {
        handleTouchDown(input);
    } else if (input.isPressed) {
        handleTouchHold(input);
    } else if (input.justReleased) {
        handleTouchUp(input);
    } else if (waitingForSecondTap_ && (input.timestamp - lastTapTime_ > config_.doubleTapTimeMs)) {
        if (lastTap_.valid) {
            sTouchEvent event;
            event.gesture = eGestureType::ONEF_TAP;
            event.x = lastTap_.x;
            event.y = lastTap_.y;
            event.startX = lastTap_.x;
            event.startY = lastTap_.y;
            event.timestamp = lastTap_.timestamp;
            pushEvent(event);
        }
        waitingForSecondTap_ = false;
        lastTap_.invalidate();
    }
}

void TouchGestureDriver::handleTouchDown(const sTouchInput& input)
{
    if (input.timestamp - lastEventTime_ < config_.debounceTimeMs) {
        return;
    }

    state_ = eTouchState::TOUCH_DOWN;
    touchStart_.set(input.x, input.y, input.timestamp);
    touchCurrent_ = touchStart_;
    longPressReported_ = false;
    dragStartReported_ = false;
    lastDragReport_ = touchStart_;

    state_ = eTouchState::WAITING_FOR_LONG_PRESS;
}

void TouchGestureDriver::handleTouchHold(const sTouchInput& input)
{
    touchCurrent_.set(input.x, input.y, input.timestamp);

    uint32_t holdDuration = input.timestamp - touchStart_.timestamp;
    int16_t distance = touchStart_.distanceTo(touchCurrent_);

    switch (state_) {
    case eTouchState::WAITING_FOR_LONG_PRESS:
        if (holdDuration >= config_.longPressTimeMs && distance < config_.tapMaxDistance) {
            sTouchEvent event;
            event.gesture = eGestureType::ONEF_LONG_PRESS;
            event.x = touchCurrent_.x;
            event.y = touchCurrent_.y;
            event.startX = touchStart_.x;
            event.startY = touchStart_.y;
            event.duration = holdDuration;
            event.timestamp = input.timestamp;
            pushEvent(event);

            state_ = eTouchState::LONG_PRESS_DETECTED;
            longPressReported_ = true;
        } else if (distance >= config_.dragMinDistance) {
            if (holdDuration > config_.swipeMaxTimeMs) {
                sTouchEvent event;
                event.gesture = eGestureType::ONEF_DRAG_START;
                event.x = touchCurrent_.x;
                event.y = touchCurrent_.y;
                event.startX = touchStart_.x;
                event.startY = touchStart_.y;
                event.deltaX = touchCurrent_.x - touchStart_.x;
                event.deltaY = touchCurrent_.y - touchStart_.y;
                event.timestamp = input.timestamp;
                pushEvent(event);

                state_ = eTouchState::DRAGGING;
                dragStartReported_ = true;
                lastDragReport_ = touchCurrent_;
            }
        }
        break;

    case eTouchState::DRAGGING: {
        sTouchEvent event;
        event.gesture = eGestureType::ONEF_DRAG_MOVE;
        event.x = touchCurrent_.x;
        event.y = touchCurrent_.y;
        event.startX = touchStart_.x;
        event.startY = touchStart_.y;
        event.deltaX = touchCurrent_.x - lastDragReport_.x;
        event.deltaY = touchCurrent_.y - lastDragReport_.y;
        event.timestamp = input.timestamp;
        pushEvent(event);

        lastDragReport_ = touchCurrent_;
    } break;

    case eTouchState::LONG_PRESS_DETECTED:
        break;

    default:
        break;
    }
}

void TouchGestureDriver::handleTouchUp(const sTouchInput& input)
{
    touchCurrent_.set(input.x, input.y, input.timestamp);

    uint32_t touchDuration = input.timestamp - touchStart_.timestamp;
    int16_t distance = touchStart_.distanceTo(touchCurrent_);

    if (state_ == eTouchState::DRAGGING) {
        sTouchEvent event;
        event.gesture = eGestureType::ONEF_DRAG_END;
        event.x = touchCurrent_.x;
        event.y = touchCurrent_.y;
        event.startX = touchStart_.x;
        event.startY = touchStart_.y;
        event.deltaX = touchCurrent_.x - touchStart_.x;
        event.deltaY = touchCurrent_.y - touchStart_.y;
        event.duration = touchDuration;
        event.timestamp = input.timestamp;
        pushEvent(event);

        lastEventTime_ = input.timestamp;
        resetState();
        return;
    }

    if (longPressReported_) {
        lastEventTime_ = input.timestamp;
        resetState();
        return;
    }

    if (distance >= config_.swipeMinDistance && touchDuration <= config_.swipeMaxTimeMs) {

        eGestureType swipeType = detectSwipe(touchStart_, touchCurrent_);
        if (swipeType != eGestureType::NONE) {
            sTouchEvent event;
            event.gesture = swipeType;
            event.x = touchCurrent_.x;
            event.y = touchCurrent_.y;
            event.startX = touchStart_.x;
            event.startY = touchStart_.y;
            event.deltaX = touchCurrent_.x - touchStart_.x;
            event.deltaY = touchCurrent_.y - touchStart_.y;
            event.duration = touchDuration;
            event.timestamp = input.timestamp;
            pushEvent(event);

            lastEventTime_ = input.timestamp;
            resetState();
            return;
        }
    }

    if (distance >= config_.dragMinDistance && touchDuration > config_.swipeMaxTimeMs) {
        lastEventTime_ = input.timestamp;
        resetState();
        return;
    }

    // Проверка тапа
    if (distance < config_.tapMaxDistance) {
        if (waitingForSecondTap_ && lastTap_.valid) {
            uint32_t timeBetweenTaps = input.timestamp - lastTapTime_;
            int16_t distanceBetweenTaps = lastTap_.distanceTo(touchCurrent_);

            if (timeBetweenTaps < config_.doubleTapTimeMs && distanceBetweenTaps < config_.doubleTapMaxDistance) {
                sTouchEvent event;
                event.gesture = eGestureType::ONEF_DOUBLE_TAP;
                event.x = touchCurrent_.x;
                event.y = touchCurrent_.y;
                event.startX = touchCurrent_.x;
                event.startY = touchCurrent_.y;
                event.timestamp = input.timestamp;
                pushEvent(event);

                waitingForSecondTap_ = false;
                lastTap_.invalidate();
                lastEventTime_ = input.timestamp;
                resetState();
                return;
            } else {
                sTouchEvent event;
                event.gesture = eGestureType::ONEF_TAP;
                event.x = lastTap_.x;
                event.y = lastTap_.y;
                event.startX = lastTap_.x;
                event.startY = lastTap_.y;
                event.timestamp = lastTap_.timestamp;
                pushEvent(event);

                waitingForSecondTap_ = false;
            }
        }

        lastTap_ = touchCurrent_;
        lastTapTime_ = input.timestamp;
        waitingForSecondTap_ = true;
    }

    lastEventTime_ = input.timestamp;
    resetState();
}

eGestureType TouchGestureDriver::detectSwipe(const TouchPoint& start, const TouchPoint& end) const
{
    int16_t dx = end.x - start.x;
    int16_t dy = end.y - start.y;

    if (abs(dx) > abs(dy)) {
        return (dx > 0) ? eGestureType::ONEF_SWIPE_RIGHT : eGestureType::ONEF_SWIPE_LEFT;
    } else {
        return (dy > 0) ? eGestureType::ONEF_SWIPE_DOWN : eGestureType::ONEF_SWIPE_UP;
    }
}

void TouchGestureDriver::pushEvent(const sTouchEvent& event)
{
    if (queueCount_ >= config_.eventQueueSize) {
        queueHead_ = (queueHead_ + 1) % config_.eventQueueSize;
        queueCount_--;
    }

    eventQueue_[queueTail_] = event;
    queueTail_ = (queueTail_ + 1) % config_.eventQueueSize;
    queueCount_++;
}

bool TouchGestureDriver::getNextEvent(sTouchEvent& event)
{
    if (queueCount_ == 0) {
        return false;
    }

    event = eventQueue_[queueHead_];
    queueHead_ = (queueHead_ + 1) % config_.eventQueueSize;
    queueCount_--;

    return true;
}

bool TouchGestureDriver::hasEvents() const
{
    return queueCount_ > 0;
}

void TouchGestureDriver::clearQueue()
{
    queueHead_ = 0;
    queueTail_ = 0;
    queueCount_ = 0;
}

void TouchGestureDriver::reset()
{
    clearQueue();
    resetState();
    lastTap_.invalidate();
    lastTapTime_ = 0;
    lastEventTime_ = 0;
    waitingForSecondTap_ = false;
}

void TouchGestureDriver::resetState()
{
    state_ = eTouchState::IDLE;
    touchStart_.invalidate();
    touchCurrent_.invalidate();
    longPressReported_ = false;
    dragStartReported_ = false;
}

void TouchGestureDriver::setConfig(const sTouchConfig& config)
{
    if (config.eventQueueSize != config_.eventQueueSize) {
        delete[] eventQueue_;
        eventQueue_ = new sTouchEvent[config.eventQueueSize];
        clearQueue();
    }

    config_ = config;
}

const sTouchConfig& TouchGestureDriver::getConfig() const
{
    return config_;
}

const char* TouchGestureDriver::getGestureName(eGestureType gesture)
{
    switch (gesture) {
    case eGestureType::ONEF_TAP:
        return "Tap";
    case eGestureType::ONEF_DOUBLE_TAP:
        return "Double Tap";
    case eGestureType::ONEF_LONG_PRESS:
        return "Long Press";
    case eGestureType::ONEF_SWIPE_UP:
        return "Swipe Up";
    case eGestureType::ONEF_SWIPE_DOWN:
        return "Swipe Down";
    case eGestureType::ONEF_SWIPE_LEFT:
        return "Swipe Left";
    case eGestureType::ONEF_SWIPE_RIGHT:
        return "Swipe Right";
    case eGestureType::ONEF_DRAG_START:
        return "Drag Start";
    case eGestureType::ONEF_DRAG_MOVE:
        return "Drag Move";
    case eGestureType::ONEF_DRAG_END:
        return "Drag End";
    default:
        return "None";
    }
}

bool TouchGestureDriver::isWithinTapThreshold(const TouchPoint& p1, const TouchPoint& p2) const
{
    return p1.distanceTo(p2) < config_.tapMaxDistance;
}

bool TouchGestureDriver::isWithinDoubleTapThreshold(const TouchPoint& p1, const TouchPoint& p2) const
{
    return p1.distanceTo(p2) < config_.doubleTapMaxDistance;
}
