#include "IntelligibleWM.h"
#include "gui/GuiRegistry.h"

#include <QApplication>
#include <QWidgetAction>
#include <QHBoxLayout>

namespace IntelligibleWM
{

    IntelligibleWM::IntelligibleWM(QWidget *parent) : QMainWindow(parent),
        _intelligibleTabWidget(nullptr)
    {
        /**
             * @brief QCoreApplication::setApplicationName set application name - Intelligible WM
             */
        QCoreApplication::setApplicationName(PROJECT_NAME_VERSION);
        setWindowTitle(PROJECT_NAME_VERSION);
        setWindowIcon(GuiRegistry::instance().intelligibleWMIcon());

        _intelligibleTabWidget = new IntelligibleTabWidget(this);

        QHBoxLayout *hlayout = new QHBoxLayout;
        hlayout->setContentsMargins(0, 3, 0, 0);
        hlayout->addWidget(_intelligibleTabWidget);
        QWidget *window = new QWidget;
        window->setLayout(hlayout);
        setCentralWidget(window);
    }

} // namespace IntelligibleWM