#include "guiregistry.h"

#include <QApplication>
#include <QIcon>
#include <QStyle>

namespace IWM
{

    /**
         * @brief GuiRegistry is a singleton
         */
    GuiRegistry::GuiRegistry()
    {
    }

    const QIcon &GuiRegistry::add() const
    {
        static const QIcon icon = QIcon(":/intelligibleWM/icons/Add.ico");
        return icon;
    }

    const QIcon &GuiRegistry::cross() const
    {
        static const QIcon icon = QIcon(":/intelligibleWM/icons/Cross.ico");
        return icon;
    }

    const QIcon &GuiRegistry::databaseIcon() const
    {
        static const QIcon icon = QIcon(":/intelligibleWM/icons/Database.ico");
        return icon;
    }

    const QIcon &GuiRegistry::intelligibleWMIcon() const
    {
        static const QIcon icon = QIcon(":/intelligibleWM/icons/IntelligibleWM.ico");
        return icon;
    }

    const QIcon &GuiRegistry::info() const
    {
        static const QIcon icon = QIcon(":/intelligibleWM/icons/Info.ico");
        return icon;
    }

    const QIcon &GuiRegistry::refresh() const
    {
        static const QIcon icon = QIcon(":/intelligibleWM/icons/Refresh.ico");
        return icon;
    }

    const QIcon &GuiRegistry::newConnection() const
    {
        static const QIcon icon = QIcon(":/intelligibleWM/icons/NewConnection.ico");
        return icon;
    }
} // namespace IWM