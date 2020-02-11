#include "IntelligibleTabWidget.h"

#include <QKeyEvent>

#include "gui/widgets/IntelligibleTabBar.h"
#include "gui/IntelligibleWidget.h"

namespace IntelligibleWM
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

        //_intelligibleWidget = new IntelligibleWidget(this);
        //addTab(_intelligibleWidget, QString(" Instance name text Test 14343"));
        //_intelligibleWidgetSecond = new IntelligibleWidget(this);
        //addTab(_intelligibleWidgetSecond, QString(" Instance name text more and more 2"));
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