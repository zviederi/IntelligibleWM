#include "IntelligibleWM.h"
#include "gui/GuiRegistry.h"
#include "gui/dialogs/AboutIntelligibleWM.h"

#include <QApplication>
#include <QWidgetAction>
#include <QHBoxLayout>
#include <QStatusBar>
#include <QMenuBar>

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

        QAction *aboutIntelligibleWMAction = new QAction("&IntelligibleWM", this);
        connect(aboutIntelligibleWMAction, SIGNAL(triggered()), this, SLOT(aboutIntelligibleWM()));

        /* About info menu */
        QMenu *helpMenu = menuBar()->addMenu("Help");
        helpMenu->addAction(aboutIntelligibleWMAction);

        menuBar()->setVisible(true);

        _intelligibleTabWidget = new IntelligibleTabWidget(this);

        QHBoxLayout *hlayout = new QHBoxLayout;
        hlayout->setContentsMargins(0, 3, 0, 0);
        hlayout->addWidget(_intelligibleTabWidget);
        QWidget *window = new QWidget;
        window->setLayout(hlayout);
        window->setWindowTitle("TEST");
        setCentralWidget(window);

        // statusBar()->setStyleSheet("QStatusBar::item { border: 0px solid black; }");
    }

    void IntelligibleWM::aboutIntelligibleWM()
    {
        AboutIntelligibleWM aboutIntelligibleWM(this);
        aboutIntelligibleWM.exec();
    }

} // namespace IntelligibleWM