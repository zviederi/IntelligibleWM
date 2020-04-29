#include "IntelligibleApp.h"

#include "core/events/bus/EventBus.h"

namespace IWM 
{
    
    /**
     * @brief  IntelligibleApp::IntelligibleApp constructor
     * @param bus
     */
    IntelligibleApp::IntelligibleApp(EventBus *const bus) : 
        QObject(), 
        _bus(bus),
        _instance(mongocxx::instance()) 
    {
        
    }

    /**
     * @brief IntelligibleApp::~IntelligibleApp destructor
     */
    IntelligibleApp::~IntelligibleApp()
    {
        _instance.~instance();
    }
}