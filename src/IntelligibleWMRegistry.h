#pragma once

#include "core/utils/singletonpattern.hpp"

#include <boost/scoped_ptr.hpp>
#include <boost/shared_ptr.hpp>

namespace IntelligibleWM
{
    class SettingsManager;
    typedef boost::scoped_ptr<SettingsManager> SettingsManagerScopedPtr;

    class IntelligibleWMEventBus;
    typedef boost::scoped_ptr<IntelligibleWMEventBus> IntelligibleWMEventBusScopedPtr;


    class IntelligibleWMRegistry : public Patterns::LazySingleton<IntelligibleWMRegistry>
    {
        friend class Patterns::LazySingleton<IntelligibleWMRegistry>;
    public:
        SettingsManager * settingsManager() const { return _settingsManager.get(); }

    private:
        IntelligibleWMRegistry();
        ~IntelligibleWMRegistry();

        const IntelligibleWMEventBusScopedPtr _intellBus;
        const SettingsManagerScopedPtr _settingsManager;
    };

} // namespace IntelligibleWM