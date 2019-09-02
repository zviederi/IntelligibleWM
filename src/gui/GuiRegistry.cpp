#include "guiregistry.h"

#include <QApplication>
#include <QIcon>
#include <QStyle>

namespace IntelligibleWM
{

    /**
         * @brief GuiRegistry is a singleton
         */
    GuiRegistry::GuiRegistry()
    {
    }

    const QIcon &GuiRegistry::intelligibleWMIcon() const
    {
        static const QIcon icon = QIcon(":/intelligibleWM/icons/IntelligibleWM.ico");
        return icon;
    }
} // namespace IntelligibleWM