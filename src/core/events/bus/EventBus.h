#pragma once

#include <QObject>
#include <QEvent>
#include <QMutex>

#include <vector>
#include <iostream>


namespace IntelligibleWM
{
    class Event;
    class EventWrapper;
    class EventBusDispatcher;
    struct EventBusSubscriber;

    class EventBus : public QObject
    {
        Q_OBJECT
    public:
        typedef std::pair<QEvent::Type, EventBusSubscriber *> SubscribersType;
        typedef std::vector<SubscribersType> SubscribersContainerType;
        typedef std::pair<QThread *, EventBusDispatcher *> DispatchersType;
        typedef std::vector<DispatchersType> DispatchersContainerType;

        EventBus(/* args */);
        ~EventBus();

        /**
         * @brief Publishes specified event.
         * @param sender - object, that emits this event
         */
        void publish(Event *event);

        /**
         * @brief Sends 'event' to 'receiver'.
         */
        void send(QObject *receiver, Event *event);

        /**
         * @brief Sends 'event' to list of 'receivers'.
         */
        void send(QList<QObject *> receivers, Event *event);

        /**
         * @brief Subscribes 'receiver' to event of specified 'type'.
         * Optionally you can specify exact send
         */
        void subscribe(QObject *receiver, QEvent::Type type, QObject *sender = nullptr);

    public Q_SLOTS:
        void unsubscibe(QObject *receiver);        

    private:
        QMutex _lock;
        SubscribersContainerType _subscribersByEventType;
        DispatchersContainerType _dispatchersByThread;

        /**
         * @brief Returns dispatcher for specified thread. If there is no dispatcher
         * for this thread registered, new dispatcher will be created and moved
         * to 'thread' thread.
         */
        EventBusDispatcher *dispatcher(QThread *thread);

        void sendEvent(EventBusDispatcher *dispatcher, EventWrapper *wrapper);

    };  

} // namespace IntelligibleWM
