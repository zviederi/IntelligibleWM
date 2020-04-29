#include "IntelligibleTabWidget.h"

#include <QKeyEvent>

#include "gui/GuiRegistry.h"
#include "gui/widgets/IntelligibleTabBar.h"
#include "gui/IntelligibleWidget.h"

namespace IWM
{
    IntelligibleTabWidget::IntelligibleTabWidget(QWidget *parent) : QTabWidget(parent)
    {
        IntelligibleTabBar *intelligibleTabBar = new IntelligibleTabBar(this);
        setElideMode(Qt::ElideRight);
        setTabBar(intelligibleTabBar);
        setTabsClosable(true);        
        setMovable(true);
        setDocumentMode(true);
        intelligibleTabBar->setIconSize(QSize(20, 20));

        _intelligibleWidget = new IntelligibleWidget(this);
        addTab(_intelligibleWidget, GuiRegistry::instance().databaseIcon(),  QString(" IWM TAB 01 "));
    }

    void IntelligibleTabWidget::closeTab(int index)
    {
        if (index >= 0)
        {
            removeTab(index);
        }
    }

    void IntelligibleTabWidget::keyPressEvent(QKeyEvent *event)
    {
        if ((event->modifiers() & Qt::ControlModifier) && event->key() == Qt::Key_W)
        {
            int index = currentIndex();
            closeTab(index);
            return;
        }
    }
} // namespace IWM