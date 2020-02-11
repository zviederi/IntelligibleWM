#include "EventBusSubscriber.h"
#include "EventBusDispatcher.h"

namespace IntelligibleWM
{
    EventBusSubscriber::EventBusSubscriber(EventBusDispatcher *dispatcher, QObject *receiver, QObject *sender):
        dispatcher(dispatcher),
        receiver(receiver),
        sender(sender)
    { }   
} // namespace IntelligibleWM