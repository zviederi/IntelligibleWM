#include "IntelligibleWMRegistry.h"

#include "core/settings/SettingsManager.h"
#include "core/events/bus/EventBus.h"

namespace IntelligibleWM
{
    IntelligibleWMRegistry::IntelligibleWMRegistry() :
        _intellBus(new EventBus()),
        _settingsManager(new SettingsManager())
    {

    }

    IntelligibleWMRegistry::~IntelligibleWMRegistry() 
    {

    }
} // namespace IntelligibleWM