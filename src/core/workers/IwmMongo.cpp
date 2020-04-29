#include "IwmMongo.h"

#include <QThread>
#include <mongocxx/exception/authentication_exception.hpp>
#include <mongocxx/exception/error_code.hpp>

#include "core/utils/utils.h"


namespace IWM {

    IwmMongo::IwmMongo(ConnectionSettings *connectionSettings, QObject *parent) : 
        QObject(parent),
        _connectionSettings(connectionSettings)
    {
        _thread = new QThread();
        moveToThread(_thread);
        VERIFY(connect(_thread, SIGNAL(finished()), _thread, SLOT(deleteLater())));
        VERIFY(connect(_thread, SIGNAL(finished()), this, SLOT(deleteLater())));
        _thread->start();
    }

    IwmMongo::~IwmMongo()
    {
        delete _connectionSettings;
    }

    void IwmMongo::quit() {
        _thread->quit();
    }

    mongocxx::client *IwmMongo::connection() 
    {
        mongocxx::instance::current();
        const auto uri = mongocxx::uri{"mongodb://localhost:27017"};
        try {
             std::cout << "Mongo Url: " << uri.to_string() << "\n";
            return new mongocxx::client{uri};
        } catch(const mongocxx::exception &ex) {
            std::cout << "connection failed: " << ex.what() << "\n";
        }
    }

}