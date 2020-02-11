#include "EventBus.h"

#include <QObject>
#include <QCoreApplication>
#include <QThread>
#include <QMutexLocker>

#include "../event.h"
#include "../eventbusdispatcher.h"
#include "../eventbussubscriber.h"
#include "../eventwrapper.h"
#include "core/utils/utils.h"

namespace IntelligibleWM {

    template < typename R, typename A > using intelligble_function = std::function< R(A) > ;

    
    struct RemoveIfReciver : public intelligble_function<const IntelligibleWM::EventBus::SubscribersType&, bool>
    {
        RemoveIfReciver(QObject *receiver) : _receiver(receiver) {}

        bool operator()(const IntelligibleWM::EventBus::SubscribersType& item) const {
            if (item.second->receiver == _receiver) {
                delete item.second;
                return true;
            }
            return false;
        }

        QObject *_receiver;
    };

    struct FindIfReciver : public intelligble_function<const IntelligibleWM::EventBus::SubscribersType&, bool>
    {
        FindIfReciver(QThread *thread) : _thread(thread) {}
        bool operator()(const IntelligibleWM::EventBus::DispatchersType &item) const {
            if (item.first == _thread) {
                return true;
            }
            return false;
        }
        QThread *_thread;
    };

    EventBus::EventBus() : QObject(),
        _lock(QMutex::Recursive)
    {}

    EventBus::~EventBus()
    {
        for (DispatchersContainerType::iterator it = _dispatchersByThread.begin(); it != _dispatchersByThread.end(); ++it) {
            DispatchersType item = *it;
            delete item.second;
        }
    }

    void EventBus::publish(Event *event)
    {
        QMutexLocker lock(&_lock);
        QList<QObject*> theReceivers;
        EventBusDispatcher *dis = nullptr;
        for (SubscribersContainerType::iterator it = _subscribersByEventType.begin(); it != _subscribersByEventType.end(); ++it ) {
            SubscribersType item = *it;
            if (event->type() == item.first) {
                EventBusSubscriber *subscriber = item.second;
                if (!subscriber->sender || subscriber->sender == event->sender()) {
                    theReceivers.append(subscriber->receiver);

                    if (dis && dis != subscriber->dispatcher) {
                        throw "You cannot publish events to subscribers from more than one thread.";
                    }

                    dis = subscriber->dispatcher;
                }
            }
        }

        if (dis) {
            sendEvent(dis, new EventWrapper(event, theReceivers));
        }
    }

    void EventBus::send(QObject *receiver, Event *event)
    {
        QMutexLocker lock(&_lock);

        if (!receiver)
            return;

        QThread *thread = receiver->thread();
        EventBusDispatcher *dis = dispatcher(thread);

        sendEvent(dis, new EventWrapper(event, receiver));
    }

    void EventBus::send(QList<QObject *> receivers, Event *event)
    {
        QMutexLocker lock(&_lock);

        if (receivers.count() == 0)
            return;

        QThread *thread = receivers.last()->thread();
        EventBusDispatcher *dis = dispatcher(thread);

        sendEvent(dis, new EventWrapper(event, receivers));
    }

    void EventBus::subscribe(QObject *receiver, QEvent::Type type, QObject *sender)
    {
        QMutexLocker lock(&_lock);

        QThread *currentThread = QThread::currentThread();
        EventBusDispatcher *dis = dispatcher(currentThread);

        /**
         * subscribe to destroyed signal in order to remove
         * listener (receiver) from list of subscribers
         */
        VERIFY(connect(receiver, SIGNAL(destroyed(QObject*)), this, SLOT(unsubscibe(QObject*))));

        /** add subscriber */
        _subscribersByEventType.push_back(SubscribersType(type, new EventBusSubscriber(dis, receiver, sender)));
    }

    void EventBus::unsubscibe(QObject *receiver)
    {
        QMutexLocker lock(&_lock);
        _subscribersByEventType.erase(std::remove_if(_subscribersByEventType.begin(), _subscribersByEventType.end(),
                                                     RemoveIfReciver(receiver)), _subscribersByEventType.end());
    }

    EventBusDispatcher *EventBus::dispatcher(QThread *thread)
    {
        DispatchersContainerType::iterator disIt = std::find_if(_dispatchersByThread.begin(), _dispatchersByThread.end(), FindIfReciver(thread));

        if (disIt != _dispatchersByThread.end()) {
            return (*disIt).second;
        }
        else {
            EventBusDispatcher *dis = new EventBusDispatcher();
            dis->moveToThread(thread);
            _dispatchersByThread.push_back(DispatchersType(thread, dis));
            return dis;
        }
    }

    void EventBus::sendEvent(EventBusDispatcher *dispatcher, EventWrapper *wrapper)
    {
        if (dispatcher->thread() == QThread::currentThread()) {
            QCoreApplication::sendEvent(dispatcher, wrapper);
            delete wrapper;
        }
        else {
            QCoreApplication::postEvent(dispatcher, wrapper);
        }
    }
}