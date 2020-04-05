#pragma once

#include "core/utils/singletonpattern.hpp"

#include <boost/scoped_ptr.hpp>
#include <boost/shared_ptr.hpp>

namespace IWM
{
    class SettingsManager;
    typedef boost::scoped_ptr<SettingsManager> SettingsManagerScopedPtr;

    class EventBus;
    typedef boost::scoped_ptr<EventBus> EventBusScopedPtr;


    class IWMRegistry : public Patterns::LazySingleton<IWMRegistry>
    {
        friend class Patterns::LazySingleton<IWMRegistry>;
    public:
        SettingsManager * settingsManager() const { return _settingsManager.get(); }

    private:
        IWMRegistry();
        ~IWMRegistry();

        const EventBusScopedPtr _intellBus;
        const SettingsManagerScopedPtr _settingsManager;
    };

} // namespace IWM