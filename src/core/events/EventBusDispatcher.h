#pragma once

#include <QObject>

namespace IntelligibleWM
{
    class EventBusDispatcher : public QObject
    {
        Q_OBJECT
    public:
        explicit EventBusDispatcher(QObject *parent = nullptr);

    protected:
        virtual bool event(QEvent *qevent);
    };
} // namespace IntelligibleWM