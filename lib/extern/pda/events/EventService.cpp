#include "EventService.h"

EventService::EventService()
{
    // Set all listners to zero (clean leastners)
    for(auto idx=0;idx<MAX_LISTENERS;idx++){
        listeners_[idx] = nullptr;
    }
}

void EventService::addListener(AEventListener *listener)
{
    // IMPROVEMENT IDEA: return bool result (false if not found)
    // Find idx of free listner cell
    auto result = -1;
    for(auto idx=0;idx<MAX_LISTENERS;idx++){
        if (listeners_[idx] == nullptr){
             result = idx;
             break;
        }
    }
    
    // Fast return
    if(result ==-1) return;

    // Add listner
    listeners_[result] = listener;
}

void EventService::removeListener(AEventListener *listener)
{
    // IMPROVEMENT IDEA: return bool result (false if not found)
    // Find idx of listner cell
    auto result = -1;
    for(auto idx=0;idx<MAX_LISTENERS;idx++){
        if (listeners_[idx] == listener){
             listeners_[idx] = nullptr;
             break;
        }
    }
}

void EventService::postEvent(const Event &event)
{
    for(auto idx=0; idx<MAX_LISTENERS;idx++){
        if(listeners_[idx] == nullptr) continue;
        listeners_[idx]->onEvent(event);
    }
}