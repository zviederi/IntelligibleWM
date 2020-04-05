#include "IWMRegistry.h"

#include "core/settings/SettingsManager.h"
#include "core/events/bus/EventBus.h"

namespace IWM
{
    IWMRegistry::IWMRegistry() :
        _intellBus(new EventBus()),
        _settingsManager(new SettingsManager())
    {

    }

    IWMRegistry::~IWMRegistry() 
    {

    }
} // namespace IWM