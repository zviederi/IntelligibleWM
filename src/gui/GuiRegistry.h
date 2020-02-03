#pragma once

#include <QAbstractItemView>
#include <QBrush>
#include <QIcon>

namespace IntelligibleWM
{

    class GuiRegistry
    {
    public:
        /**
             * @brief Returns single instance of GuiRegistry
             */
        static GuiRegistry &instance()
        {
            static GuiRegistry _instance;
            return _instance;
        }

        const QIcon &add() const;
        const QIcon &cross() const;
        const QIcon &databaseIcon() const;
        const QIcon &intelligibleWMIcon() const;
        const QIcon &info() const;
        const QIcon &refresh() const;
        const QIcon &newConnection() const;

    private:
        GuiRegistry();
    };

} // namespace IntelligibleWM
