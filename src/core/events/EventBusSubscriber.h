#pragma once

#include <QObject>

namespace IntelligibleWM
{
    class EventBusDispatcher;
    struct EventBusSubscriber
    {
        EventBusSubscriber(EventBusDispatcher *dispatcher, QObject *receiver, QObject *sender = nullptr);
        EventBusDispatcher *const dispatcher;
        QObject *const receiver;
        QObject *const sender;
    };
} // namespace IntelligibleWM