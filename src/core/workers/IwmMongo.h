#pragma once

#include <QObject>
#include <QMutex>

#include <iostream>
#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>
#include <mongocxx/uri.hpp>

namespace IWM {
    
    class IwmMongo : public QObject
    {
        Q_OBJECT
    public:
        explicit IwmMongo(QObject *parent = nullptr);

    private:
        QThread *_thread;

        mongocxx::client *connection();
    };  

}