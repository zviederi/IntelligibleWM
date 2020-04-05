#pragma once

#include <QFrame>
#include <QToolButton>

namespace IWM
{
    class IntelligibleToolBar : public QFrame
    {
        Q_OBJECT
    public:
        typedef QFrame BaseClass;
        explicit IntelligibleToolBar(QWidget *parent);

    private:
        QToolButton *const _refresh;
    };

} // namespace IWM