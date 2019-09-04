#pragma once

#include <QWidget>
#include <QSplitter>
#include <QListView>

#include "gui/widgets/IntelligibleToolBar.h"

namespace IntelligibleWM
{
    class IntelligibleWidget : public QWidget
    {
        Q_OBJECT

    public:
        explicit IntelligibleWidget(QWidget *parent = nullptr);

    private:
        IntelligibleToolBar *const _toolBar;
        QSplitter *const _verticalSplitter;
    };

} // namespace IntelligibleWM