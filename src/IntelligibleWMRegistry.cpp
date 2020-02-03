#include "IntelligibleWMRegistry.h"

#include "core/settings/SettingsManager.h"
#include "core/events/IntelligibleWMEventBus.h"

namespace IntelligibleWM
{
    IntelligibleWMRegistry::IntelligibleWMRegistry() :
        _dellBus(new IntelligibleWMEventBus()),
        _settingsManager(new SettingsManager())
    {

    }

    IntelligibleWMRegistry::~IntelligibleWMRegistry() 
    {

    }
} // namespace IntelligibleWM