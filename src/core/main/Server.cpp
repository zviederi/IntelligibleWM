#include "Server.h"

#include "core/settings/ConnectionSettings.h"
#include "core/workers/IwmMongo.h"
#include "Registry.h"

namespace IWM 
{
    Server::Server(ConnectionSettings *connectionSettings, QObject *parent) :
        QObject(parent),
        _bus(Registry::instance().eventBus()),
        _mongoWorker(new IwmMongo(connectionSettings->clone()))
    {

    }

    Server::~Server() 
    {
        if (_mongoWorker != nullptr) 
        {
            _mongoWorker->quit();
        }
    }
} // namespace IWM