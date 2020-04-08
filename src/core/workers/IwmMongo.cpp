#include "IwmMongo.h"

#include <QThread>

#include <mongocxx/exception/authentication_exception.hpp>
#include <mongocxx/exception/error_code.hpp>


namespace IWM {

    IwmMongo::IwmMongo(QObject *parent ) : QObject(parent) 
    {
        
    }

    mongocxx::client *IwmMongo::connection() 
    {
        mongocxx::instance::current();
        const auto uri = mongocxx::uri{"mongodb://localhost:27017"};
        try {
            return new mongocxx::client{uri};
        } catch(const mongocxx::exception &ex) {
            std::cout << "connection failed: " << ex.what() << "\n";
        }
    }

}