#pragma once

#include <QObject>

namespace IWM 
{
    class EventBus;
    class IwmMongo;
    class ConnectionSettings;

    class Server : public QObject
    {
        Q_OBJECT
    public:
        Server(ConnectionSettings *connectionSettings, QObject *parent = nullptr);
        ~Server();
    private:
        EventBus *_bus;

        /**
         * Mongo worker which use threads
         */
        IwmMongo *const _mongoWorker;
    };
    
} // namespace IWM