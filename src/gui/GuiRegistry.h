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

        const QIcon &intelligibleWMIcon() const;
        const QIcon &refresh() const;

    private:
        GuiRegistry();
    };

} // namespace IntelligibleWM
