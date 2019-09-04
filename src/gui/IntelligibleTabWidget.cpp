#include "IntelligibleTabWidget.h"

#include <QKeyEvent>

#include "gui/widgets/IntelligibleTabBar.h"
#include "gui/IntelligibleWidget.h"

namespace IntelligibleWM
{
    IntelligibleTabWidget::IntelligibleTabWidget(QWidget *parent) : QTabWidget(parent)
    {
        IntelligibleTabBar *intelligibleTabBar = new IntelligibleTabBar(this);
        setTabBar(intelligibleTabBar);
        setTabsClosable(true);
        setElideMode(Qt::ElideRight);
        setMovable(true);
        setDocumentMode(true);
        intelligibleTabBar->setIconSize(QSize(20, 20));

        _intelligibleWidget = new IntelligibleWidget(this);
        addTab(_intelligibleWidget, QString(" Instance name "));
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
} // namespace IntelligibleWM