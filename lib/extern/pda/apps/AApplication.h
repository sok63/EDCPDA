#pragma once 

#include <stdint.h>

#include <pda/hal/ADisplayHAL.h>
#include <pda/events/EventService.h>

enum class eApplicationState { STOPPED, RUNNING, PAUSED };

class AApplication : public AEventListener {
public:
    virtual ~AApplication() = default;
    
    // Lifecycle methods
    virtual void onCreate();
    virtual void onStart();
    virtual void onResume();
    virtual void onPause();
    virtual void onStop();
    
    // Update loop
    virtual void update(uint32_t deltaTime) = 0;
    bool needRedraw();
    virtual void render() = 0;
    
    // App info
    eApplicationState getState();
    virtual const char* getName() const = 0;
    virtual const char* getDescription() const = 0;
    virtual const uint8_t* getIcon() const = 0; // 64x64 icon data
    
    // Event handling from IEventListener
    virtual void onEvent(const Event& event) override = 0;

protected:
    bool needRedraw_ = true;
    eApplicationState state_ = eApplicationState::STOPPED;
};