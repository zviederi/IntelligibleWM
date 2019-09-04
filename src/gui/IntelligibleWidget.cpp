#include "IntelligibleWidget.h"

#include <QVBoxLayout>

namespace IntelligibleWM
{
    IntelligibleWidget::IntelligibleWidget(QWidget *parent) : QWidget(parent),
        _toolBar(new IntelligibleToolBar(this)),
        _verticalSplitter(new QSplitter(this))
    {
        _toolBar->setVisible(true);

        _verticalSplitter->setOrientation(Qt::Vertical);
        _verticalSplitter->setHandleWidth(1);
        _verticalSplitter->setContentsMargins(0, 0, 0, 0);

        QList<int> vSizes;
        vSizes << width() << width();
        _verticalSplitter->setSizes(vSizes);

        QVBoxLayout *layout = new QVBoxLayout();
        layout->setContentsMargins(0, 0, 0, 0);
        layout->addWidget(_toolBar, 0);
        layout->setSpacing(0);
        layout->addWidget(_verticalSplitter, 1);
        setLayout(layout);
    }
} // namespace IntelligibleWM