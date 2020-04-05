#include "EventBusSubscriber.h"
#include "EventBusDispatcher.h"

namespace IWM
{
    EventBusSubscriber::EventBusSubscriber(EventBusDispatcher *dispatcher, QObject *receiver, QObject *sender):
        dispatcher(dispatcher),
        receiver(receiver),
        sender(sender)
    { }   
} // namespace IWM