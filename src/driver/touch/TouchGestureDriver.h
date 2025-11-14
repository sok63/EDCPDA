#pragma once

#include <cstdint>

#include <pda/core/TouchPrimitives.h>


struct sTouchInput {
    int16_t x;
    int16_t y;
    bool isPressed;        
    bool justPressed;      
    bool justReleased;     
    uint32_t timestamp;     
    
    sTouchInput() : x(0), y(0), isPressed(false), 
                    justPressed(false), justReleased(false), 
                    timestamp(0) {}
};

struct sTouchConfig {
    uint32_t doubleTapTimeMs;      
    uint32_t longPressTimeMs;      
    uint32_t debounceTimeMs;     
    uint32_t swipeMaxTimeMs; 
    int16_t tapMaxDistance;        
    int16_t doubleTapMaxDistance;  
    int16_t swipeMinDistance;       
    int16_t dragMinDistance;      
    uint8_t eventQueueSize;        
    
    sTouchConfig() :
        doubleTapTimeMs(180),
        longPressTimeMs(500),
        debounceTimeMs(30),
        tapMaxDistance(10),
        doubleTapMaxDistance(80),
        swipeMinDistance(50),
        swipeMaxTimeMs(400),  
        dragMinDistance(15),
        eventQueueSize(8) {}
};


class TouchGestureDriver {
public:
    TouchGestureDriver(const sTouchConfig& config = sTouchConfig());
    ~TouchGestureDriver();
    
    void update(const sTouchInput& input);
    
    bool getNextEvent(sTouchEvent& event);
    bool hasEvents() const;
    void reset();
    
    void setConfig(const sTouchConfig& config);
    const sTouchConfig& getConfig() const;
    
    static const char* getGestureName(eGestureType gesture);

private:
    struct TouchPoint {
        int16_t x;
        int16_t y;
        uint32_t timestamp;
        bool valid;
        
        TouchPoint() : x(0), y(0), timestamp(0), valid(false) {}
        
        void set(int16_t _x, int16_t _y, uint32_t _timestamp) {
            x = _x;
            y = _y;
            timestamp = _timestamp;
            valid = true;
        }
        
        void invalidate() {
            valid = false;
        }
        
        int16_t distanceTo(const TouchPoint& other) const;
    };
    
    enum class eTouchState : uint8_t {
        IDLE,
        TOUCH_DOWN,
        WAITING_FOR_LONG_PRESS,
        LONG_PRESS_DETECTED,
        DRAGGING,
        TOUCH_RELEASED
    };
    
    sTouchConfig config_;
    
    eTouchState state_;
    TouchPoint touchStart_;         
    TouchPoint touchCurrent_;       
    TouchPoint lastTap_;            
    TouchPoint lastDragReport_;         
    uint32_t lastTapTime_;          
    uint32_t lastEventTime_;        
    bool waitingForSecondTap_;  
    bool longPressReported_;       
    bool dragStartReported_;      
    
    sTouchEvent* eventQueue_;
    uint8_t queueHead_;
    uint8_t queueTail_;
    uint8_t queueCount_;
    
    void handleTouchDown(const sTouchInput& input);
    void handleTouchHold(const sTouchInput& input);
    void handleTouchUp(const sTouchInput& input);
    
    void pushEvent(const sTouchEvent& event);
    void clearQueue();
    
    bool isWithinTapThreshold(const TouchPoint& p1, const TouchPoint& p2) const;
    bool isWithinDoubleTapThreshold(const TouchPoint& p1, const TouchPoint& p2) const;
    
    eGestureType detectSwipe(const TouchPoint& start, const TouchPoint& end) const;
    
    void resetState();
};
