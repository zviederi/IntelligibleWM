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

    class IntelligibleApp;
    typedef boost::scoped_ptr<IntelligibleApp> IntelligibleAppScopedPtr;

    class Registry : public Patterns::LazySingleton<Registry>
    {
        friend class Patterns::LazySingleton<Registry>;
    public:
        EventBus * eventBus() const { return _bus.get(); }
        SettingsManager * settingsManager() const { return _settingsManager.get(); }
        IntelligibleApp * intelligibleApp() const { return _intelligibleApp.get(); }

    private:
        Registry();
        ~Registry();

        const EventBusScopedPtr _bus;
        const SettingsManagerScopedPtr _settingsManager;
        const IntelligibleAppScopedPtr _intelligibleApp;
    };

} // namespace IWM