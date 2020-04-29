#pragma once

#include <QObject>
#include <mongocxx/instance.hpp>

namespace IWM
{
    class EventBus;

    class IntelligibleApp : public QObject
    {
        Q_OBJECT
    public:
        /**
         * @brief Constructor who initialize Intelligible app with event bus.
         * @param bus
         */
        IntelligibleApp(EventBus *const bus);

        /**
         * Deconstructor of intelligible app.
         */
        ~IntelligibleApp();
    private:
        /**
         * @brief _bus
         */
        EventBus *const _bus;

        /**
         * @brief _instance
         */
        mongocxx::instance _instance;

    };
    
} // namespace IWM