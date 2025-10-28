#pragma once 

#include <stdint.h>

#include <pda/hal/ADisplayHAL.h>
#include <pda/sal/EventService.h>

enum class eApplicationState { STOPPED, RUNNING, PAUSED };

class AApplication : public AEventListener {
public:
    virtual ~AApplication() = default;
    
    // Lifecycle methods
    virtual void onCreate() = 0;
    virtual void onStart() = 0;
    virtual void onResume() = 0;
    virtual void onPause() = 0;
    virtual void onStop() = 0;
    
    // Update loop
    virtual void update(uint32_t deltaTime) = 0;
    virtual void render(ADisplayHAL* display) = 0;
    
    // App info
    eApplicationState getState();
    virtual const char* getName() const = 0;
    virtual const char* getDescription() const = 0;
    virtual const uint8_t* getIcon() const = 0; // 64x64 icon data
    
    // Event handling from IEventListener
    virtual void onEvent(const Event& event) override = 0;

protected:
    eApplicationState state_ = eApplicationState::STOPPED;
};