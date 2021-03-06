#include "IntelligibleWM.h"

#include <QApplication>
#include <QWidgetAction>
#include <QHBoxLayout>
#include <QStatusBar>
#include <QMenuBar>

#include "Registry.h"

#include "gui/GuiRegistry.h"
#include "gui/dialogs/AboutIntelligibleWM.h"
#include "gui/dialogs/ConnectionIntelligibleWM.h"

#include "core/settings/SettingsManager.h"
#include "core/events/bus/EventBus.h"
#include "core/utils/utils.h"

namespace IWM
{

    IntelligibleWM::IntelligibleWM(QWidget *parent) : QMainWindow(parent),
        _intelligibleTabWidget(nullptr)
    {
        /**
         * @brief Set application name - Intelligible WM
         */
        QCoreApplication::setApplicationName(PROJECT_NAME_VERSION);
        setWindowTitle(PROJECT_NAME_VERSION);
        setWindowIcon(GuiRegistry::instance().intelligibleWMIcon());

        QString controlKey = "Ctrl";

        QAction *aboutIntelligibleWMAction = new QAction("&IntelligibleWM", this);
        VERIFY(connect(aboutIntelligibleWMAction, SIGNAL(triggered()), this, SLOT(aboutIntelligibleWM())));

        QAction *connectAction = new QAction(tr("New &Connection..."), this);
        connectAction->setShortcuts(QKeySequence::New);
        connectAction->setIconText(tr("New &Connection"));
        connectAction->setToolTip(QString("Connect to warehouse. <b>(%1 + N)</b>").arg(controlKey));
        VERIFY(connect(connectAction, SIGNAL(triggered()), this, SLOT(openConnectionDialog())));

          /* Quit action */
        QAction *quitAction = new QAction("&Quit", this);
        quitAction->setShortcuts(QKeySequence::Quit);
        VERIFY(connect(quitAction, SIGNAL(triggered()), this, SLOT(close())));

        /* File menu */
        QMenu *fileMenu = menuBar()->addMenu(tr("File"));
        fileMenu->addAction(connectAction);
        fileMenu->addAction(quitAction);

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
        setCentralWidget(window);
    }

    void IntelligibleWM::aboutIntelligibleWM()
    {
        AboutIntelligibleWM aboutIntelligibleWM(this);
        aboutIntelligibleWM.exec();
    }

    void IntelligibleWM::openConnectionDialog()
    {
        ConnectionIntelligibleWM dialog(Registry::instance().settingsManager(), this);
        int result = dialog.exec();

        if (result == QDialog::Accepted) {
            ConnectionSettings *selected = dialog.selectedConnection();
         //   openServer(selected);
        }
    }

} // namespace IWM