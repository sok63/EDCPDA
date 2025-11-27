#pragma once

#include <pda/core/CorePrimitives.h>
#include <pda/core/events/EventService.h>
#include <pda/hal/interfaces/ADisplaySpriteHAL.h>

class AWidget
{
public:
    AWidget(sRect size);
    virtual ~AWidget() = default;

    virtual void update() = 0;
    virtual void render(ADisplaySpriteHAL* render_to) = 0;

    virtual bool feed_event(const Event& ev)
    {
        return false;
    };

    bool take_dirty_flag();
    void set_dirty_flag();

    void set_new_size(sRect);
    sRect& get_size();

protected:
    bool dirty_ = false;
    sRect size_;
};