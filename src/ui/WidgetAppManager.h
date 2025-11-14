#pragma once

#include <list>

#include "AWidget.h"

class WidgetAppManager
{
public:
    std::list<AWidget*>* listnersList();
    std::list<AWidget*>* renderList();

    void push_back(AWidget*);
    void push_front(AWidget*);

private:
    std::list<AWidget*> w_event_listners_;
    std::list<AWidget*> w_render_;
};