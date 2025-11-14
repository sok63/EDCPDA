#pragma once

#include <stdint.h>

#include <pda/events/EventService.h>
#include <pda/hal/ADisplayHAL.h>
#include <pda/hal/ADisplaySpriteHAL.h>

enum class eApplicationState
{
    STOPPED,
    RUNNING,
    PAUSED
};

class AApplication : public AEventListener
{
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
    virtual void render() = 0;

    // App info
    eApplicationState getState();
    virtual const char* getName() const = 0;
    virtual void drawIconTo(ADisplaySpriteHAL*) = 0;

    // Event handling from IEventListener
    virtual bool onEvent(const Event& event) override = 0;

protected:
    eApplicationState state_ = eApplicationState::STOPPED;
};