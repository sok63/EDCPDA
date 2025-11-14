#include "WidgetAppManager.h"

std::list<AWidget *> *WidgetAppManager::listnersList()
{
    return &w_event_listners_;
}

std::list<AWidget *> *WidgetAppManager::renderList()
{
    return &w_render_;
}

void WidgetAppManager::push_back(AWidget *w)
{
    w_render_.push_back(w);
    w_event_listners_.push_back(w);
}

void WidgetAppManager::push_front(AWidget *w)
{
    w_render_.push_front(w);
    w_event_listners_.push_front(w);
}
