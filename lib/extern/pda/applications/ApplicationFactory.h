#pragma once

#include <cstdint>

#include <pda/applications/AApplication.h>
#include <pda/hal/interfaces/ADisplaySpriteHAL.h>

using AppFactoryFn = AApplication* (*) (void);
using IconDrawFn = void (*)(ADisplaySpriteHAL*);

struct AppDescriptor
{
    uint32_t id;
    const char* name;
    AppFactoryFn create;
    IconDrawFn drawIcon;
};

class AppFactory
{
public:
    AppFactory(AppDescriptor* apps, size_t count)
        : m_apps(apps)
        , m_count(count)
    {
    }

    AppDescriptor* getByIndex(size_t idx) const
    {
        return (idx < m_count) ? &m_apps[idx] : nullptr;
    }

    AppDescriptor* getById(uint32_t id) const
    {
        for (size_t i = 0; i < m_count; ++i)
            if (m_apps[i].id == id)
                return &m_apps[i];
        return nullptr;
    }

    AApplication* create(uint32_t id) const
    {
        auto* d = getById(id);
        return (d && d->create) ? d->create() : nullptr;
    }

    size_t count() const
    {
        return m_count;
    }

private:
    AppDescriptor* m_apps;
    size_t m_count;
};
