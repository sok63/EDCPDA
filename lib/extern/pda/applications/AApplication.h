#pragma once

#include <stdint.h>

#include <pda/core/events/EventService.h>
#include <pda/hal/interfaces/ADisplayHAL.h>
#include <pda/hal/interfaces/ADisplaySpriteHAL.h>

class AApplication : public AEventListener
{
public:
    virtual ~AApplication() = default;

    // Update loop
    virtual void update(uint32_t deltaTime) = 0;
    virtual void render() = 0;

    // Event handling from IEventListener
    virtual bool onEvent(const Event& event) override = 0;
};