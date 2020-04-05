#include "IntelligibleToolBar.h"

#include <QHBoxLayout>

#include "gui/GuiRegistry.h"

namespace IWM
{
    IntelligibleToolBar::IntelligibleToolBar(QWidget *parent) : BaseClass(parent),
        _refresh(new QToolButton(this))
    {
        _refresh->setIcon(GuiRegistry::instance().refresh());
        _refresh->setToolButtonStyle(Qt::ToolButtonIconOnly);        
        _refresh->setIconSize(QSize(45, 19));
   
        QHBoxLayout *mainLayout = new QHBoxLayout();
        mainLayout->setContentsMargins(2, 2, 2, 0);
        mainLayout->setSpacing(2);
        mainLayout->addWidget(_refresh, 0, Qt::AlignCenter);
        setLayout(mainLayout);
    }

} // namespace IWM 