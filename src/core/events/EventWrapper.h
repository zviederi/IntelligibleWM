#pragma once

#include <QEvent>
#include <boost/scoped_ptr.hpp>

#include "Event.h"

namespace IWM
{
    class EventWrapper : public QEvent
    {
    public:
        EventWrapper(Event *event, QList<QObject *> receivers);
        EventWrapper(Event *event, QObject * receiver);
        Event *event() const;
        const QList<QObject *> &receivers() const;

    private:
        const boost::scoped_ptr<Event> _event;
        const QList<QObject *> _receivers;
    };
} // namespace IWM