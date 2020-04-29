#include "Registry.h"

#include "core/events/bus/EventBus.h"
#include "core/settings/SettingsManager.h"
#include "IntelligibleApp.h"

namespace IWM
{
    Registry::Registry() :
        _bus(new EventBus()),
        _settingsManager(new SettingsManager()),
        _intelligibleApp(new IntelligibleApp(_bus.get()))
    { }

    Registry::~Registry() 
    { }
} // namespace IWM