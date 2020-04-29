#pragma once

#include <QObject>
#include <QMutex>

#include <iostream>
#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>
#include <mongocxx/uri.hpp>

namespace IWM {
    
    class ConnectionSettings;

    class IwmMongo : public QObject
    {
        Q_OBJECT
    public:
        /**
         * @brief Constructor which initialize a mongo worker in new thread
         * @param bus
         */
        explicit IwmMongo(ConnectionSettings *connectionSettings, QObject *parent = nullptr);

        /**
         * Deconstructor/delete worker and thread
         */
        ~IwmMongo();

        /**
         * Quit from thread
         */
        void quit();

        ConnectionSettings *connectionSettings() const {
            return _connectionSettings;
        }

    private:
        QThread *_thread;

        ConnectionSettings *_connectionSettings;

        mongocxx::client *connection();
    };  

} // namespace IWM